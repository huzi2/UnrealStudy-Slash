// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Enemy.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/HealthBarComponent.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "AIController.h"
#include "Components/AttributeComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "Items/Weapons/Weapon.h"

AEnemy::AEnemy()
	: DeathPose(EDeathPose::EDP_Alive)
	, CombatRadius(500.0)
	, AttackRadius(150.0)
	, PatrolRadius(200.0)
	, WaitMin(5.f)
	, WaitMax(10.f)
	, EnemyState(EEnemyState::EES_Patrolling)
{
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	HealthBarWidget = CreateDefaultSubobject<UHealthBarComponent>(TEXT("HealthBar"));
	HealthBarWidget->SetupAttachment(GetRootComponent());

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	PawnSensing->SightRadius = 4000.f;
	PawnSensing->SetPeripheralVisionAngle(45.f);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void AEnemy::GetHit_Implementation(const FVector& ImpactPoint)
{
	//DRAW_SPHERE_COLOR(ImpactPoint, FColor::Orange);
	if (HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(true);
	}

	if (Attributes && Attributes->IsAlive())
	{
		DirectionalHitReact(ImpactPoint);
	}
	else
	{
		Die();
	}

	if (HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, ImpactPoint);
	}

	if (HitParticles && GetWorld())
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, ImpactPoint);
	}
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(false);
	}

	EnemyController = Cast<AAIController>(GetController());
	MoveToTarget(PatrolTarget);

	if (PawnSensing)
	{
		PawnSensing->OnSeePawn.AddDynamic(this, &AEnemy::PawnSee);
	}

	UWorld* World = GetWorld();
	if (World && WeaponClass)
	{
		AWeapon* DefaultWeapon = World->SpawnActor<AWeapon>(WeaponClass);
		if (DefaultWeapon)
		{
			DefaultWeapon->Equip(GetMesh(), TEXT("RightHandSocket"), this, this);
			EquippedWeapon = DefaultWeapon;
		}
	}
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (EnemyState > EEnemyState::EES_Patrolling)
	{
		CheckCombatTarget();
	}
	else
	{
		CheckPatrolTarget();
	}
}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if(Attributes)
	{
		Attributes->ReceiveDamage(DamageAmount);

		if (HealthBarWidget)
		{
			HealthBarWidget->SetHealthBarPercent(Attributes->GetHealthPercent());
		}
	}

	if (EventInstigator)
	{
		CombatTarget = EventInstigator->GetPawn();

		GetCharacterMovement()->MaxWalkSpeed = 300.f;
		EnemyState = EEnemyState::EES_Chasing;
		MoveToTarget(CombatTarget);
	}

	return 0.0f;
}

void AEnemy::Destroyed()
{
	Super::Destroyed();

	if (EquippedWeapon)
	{
		EquippedWeapon->Destroy();
	}
}

void AEnemy::Die()
{
	if (!DeathMontage) return;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->Montage_Play(DeathMontage);

		FName SectionName = FName();
		const int32 Selection = FMath::RandRange(0, 5);
		switch (Selection)
		{
		case 0:
			SectionName = TEXT("Death1");
			DeathPose = EDeathPose::EDP_Death1;
			break;
		case 1:
			SectionName = TEXT("Death2");
			DeathPose = EDeathPose::EDP_Death2;
			break;
		case 2:
			SectionName = TEXT("Death3");
			DeathPose = EDeathPose::EDP_Death3;
			break;
		case 3:
			SectionName = TEXT("Death4");
			DeathPose = EDeathPose::EDP_Death4;
			break;
		case 4:
			SectionName = TEXT("Death5");
			DeathPose = EDeathPose::EDP_Death5;
			break;
		case 5:
			SectionName = TEXT("Death6");
			DeathPose = EDeathPose::EDP_Death6;
			break;
		default:
			break;
		}

		AnimInstance->Montage_JumpToSection(SectionName, DeathMontage);
	}

	if (HealthBarWidget)
	{
		HealthBarWidget->SetVisibility(false);
	}

	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	SetLifeSpan(3.f);
}

void AEnemy::PawnSee(APawn* SeenPawn)
{
	if (EnemyState == EEnemyState::EES_Chasing) return;

	if (SeenPawn->ActorHasTag(TEXT("SlashCharacter")))
	{
		GetWorldTimerManager().ClearTimer(PatrolTimer);
		GetCharacterMovement()->MaxWalkSpeed = 300.f;
		CombatTarget = SeenPawn;

		if (EnemyState != EEnemyState::EES_Attacking)
		{
			EnemyState = EEnemyState::EES_Chasing;
			MoveToTarget(CombatTarget);
		}
	}
}

void AEnemy::CheckCombatTarget()
{
	if (!CombatTarget) return;

	// 타겟이 전투 거리를 벗어남. 다시 패트롤 시작
	if (!InTargetRange(CombatTarget, CombatRadius))
	{
		CombatTarget = nullptr;
		if (HealthBarWidget)
		{
			HealthBarWidget->SetVisibility(false);
		}
		GetCharacterMovement()->MaxWalkSpeed = 125.f;
		EnemyState = EEnemyState::EES_Patrolling;
			
		MoveToTarget(PatrolTarget);
	}
	// 타겟이 공격 거리를 벗어남. 추적으로 전환
	else if (!InTargetRange(CombatTarget, AttackRadius) && EnemyState != EEnemyState::EES_Chasing)
	{
		GetCharacterMovement()->MaxWalkSpeed = 300.f;
		EnemyState = EEnemyState::EES_Chasing;

		MoveToTarget(CombatTarget);
	}
	// 타겟이 공격 거리 안에 있음. 공격 시작
	else if (InTargetRange(CombatTarget, AttackRadius) && EnemyState != EEnemyState::EES_Attacking)
	{
		EnemyState = EEnemyState::EES_Attacking;
	}
}

void AEnemy::CheckPatrolTarget()
{
	if (InTargetRange(PatrolTarget, PatrolRadius))
	{
		PatrolTarget = ChoosePatrolTarget();
		const float WaitTime = FMath::RandRange(WaitMin, WaitMax);
		GetWorldTimerManager().SetTimer(PatrolTimer, this, &AEnemy::PatrolTimerFinished, WaitTime);
	}
}

const bool AEnemy::InTargetRange(AActor* Target, double Radius) const
{
	if (!Target) return false;

	const double DistanceToTarget = (Target->GetActorLocation() - GetActorLocation()).Size();
	return DistanceToTarget <= Radius;
}

void AEnemy::MoveToTarget(AActor* Target)
{
	if (!EnemyController || !Target) return;

	FAIMoveRequest MoveRequest;
	MoveRequest.SetGoalActor(Target);
	MoveRequest.SetAcceptanceRadius(15.f);
	EnemyController->MoveTo(MoveRequest);
}

AActor* AEnemy::ChoosePatrolTarget() const
{
	if (PatrolTargets.Num() < 2) return nullptr;

	TArray<AActor*> ValidTargets;
	ValidTargets.Reserve(PatrolTargets.Num() - 1);
	for (AActor* Target : PatrolTargets)
	{
		if (Target != PatrolTarget)
		{
			ValidTargets.AddUnique(Target);
		}
	}

	const int32 NumPatrolTargets = ValidTargets.Num();
	const int32 TargetSelection = FMath::RandRange(0, NumPatrolTargets - 1);
	return ValidTargets[TargetSelection];
}

void AEnemy::PatrolTimerFinished()
{
	MoveToTarget(PatrolTarget);
}
