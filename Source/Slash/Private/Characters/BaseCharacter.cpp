// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"
#include "Items/Weapons/Weapon.h"
#include "Components/BoxComponent.h"
#include "Components/AttributeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

ABaseCharacter::ABaseCharacter()
	: WarpTargetDistance(75.f)
{
	PrimaryActorTick.bCanEverTick = false;

	Attributes = CreateDefaultSubobject<UAttributeComponent>(TEXT("Attributes"));

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
}

void ABaseCharacter::GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter)
{
	if (IsAlive() && Hitter)
	{
		DirectionalHitReact(Hitter->GetActorLocation());
	}
	else
	{
		Die();
	}

	PlayHitSound(ImpactPoint);
	SpawnHitParticles(ImpactPoint);
	SetWeaponCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABaseCharacter::AttackEnd()
{
	if (CombatTarget && CombatTarget->ActorHasTag(TEXT("Dead")))
	{
		CombatTarget = nullptr;
	}
}

const bool ABaseCharacter::CanAttack() const
{
	return false;
}

void ABaseCharacter::Attack()
{
}

void ABaseCharacter::Die()
{
	Tags.Add(TEXT("Dead"));
	PlayDeathMontage();
}

void ABaseCharacter::HandleDamage(const float DamageAmount)
{
	if (Attributes)
	{
		Attributes->ReceiveDamage(DamageAmount);
	}
}

const int32 ABaseCharacter::PlayAttackMontage()
{
	return PlayRandomMontageSection(AttackMontage, AttackMontageSections);
}

const int32 ABaseCharacter::PlayDeathMontage()
{
	const int32 Selection = PlayRandomMontageSection(DeathMontage, DeathMontageSections);
	TEnumAsByte<EDeathPose> Pose(Selection);
	if (Pose < EDeathPose::EDP_MAX)
	{
		DeathPose = Pose;
	}

	return Selection;
}

void ABaseCharacter::SetWeaponCollisionEnabled(const ECollisionEnabled::Type CollisionEnabled)
{
	if (EquippedWeapon && EquippedWeapon->GetWeaponBox())
	{
		EquippedWeapon->GetWeaponBox()->SetCollisionEnabled(CollisionEnabled);
		EquippedWeapon->IgnoreActors.Empty();
	}
}

const FVector ABaseCharacter::GetTranslationWarpTarget() const
{
	// 타겟에서 일정거리(WarpTargetDistance) 떨어진 만큼의 위치를 구함
	if (CombatTarget)
	{
		const FVector& CombatTargetLocation = CombatTarget->GetActorLocation();
		const FVector& Location = GetActorLocation();

		FVector TargetToMe = (Location - CombatTargetLocation).GetSafeNormal();
		TargetToMe *= WarpTargetDistance;
		return CombatTargetLocation + TargetToMe;
	}
	return FVector();
}

const FVector ABaseCharacter::GetRotationWarpTarget() const
{
	if (CombatTarget)
	{
		return CombatTarget->GetActorLocation();
	}
	return FVector();
}

const bool ABaseCharacter::IsAlive() const
{
	return Attributes && Attributes->IsAlive();
}

void ABaseCharacter::PlayHitReactMontage(const FName& SectionName)
{
	if (!HitReactMontage) return;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->Montage_Play(HitReactMontage);
		AnimInstance->Montage_JumpToSection(SectionName, HitReactMontage);
	}
}

void ABaseCharacter::DirectionalHitReact(const FVector& ImpactPoint)
{
	// 들어오는 공격이 어디쪽인지 확인. 전방벡터와 원점->공격지점 벡터끼리 내적
	const FVector Forward = GetActorForwardVector();
	const FVector ImpactLowered(ImpactPoint.X, ImpactPoint.Y, GetActorLocation().Z);
	const FVector ToHit = (ImpactLowered - GetActorLocation()).GetSafeNormal();

	// 내적값에 Acos하면 각도가 나온다(|A|*|B| = cos(theta))
	const double CosTheta = FVector::DotProduct(Forward, ToHit);
	double Theta = FMath::Acos(CosTheta);
	Theta = FMath::RadiansToDegrees(Theta);

	// 하지만 위 결과로는 양수만 나와서 각도는 알아도 왼쪽인지 오른쪽인지 알수가 없다. 그래서 외적함
	// 언리얼엔진에서 외적은 왼손법칙을 따르며 검지와 중지의 외적이 엄지를 따른다.
	// 그래서 엄지 위치(Z값)가 위인지 아래(0보다 작음)인지 확인해서 왼쪽인지 오른쪽인지 확인
	// 왼손으로 검지를 전방벡터, 중지를 히트포인트로 생각하면 중지가 오른쪽일때 엄지가 위로간다
	const FVector CrossProduct = FVector::CrossProduct(Forward, ToHit);
	// 엄지(Z값)가 아래(0보다 작음)이므로 방향은 왼쪽
	if (CrossProduct.Z < 0.0)
	{
		Theta *= -1.f;
	}

	// -135 ~ 135도
	FName Section(TEXT("FromBack"));

	if (Theta >= -45.f && Theta < 45.f)
	{
		Section = TEXT("FromFront");
	}
	else if (Theta >= -135.f && Theta < -45.f)
	{
		Section = TEXT("FromLeft");
	}
	else if (Theta >= 45.f && Theta < 135.f)
	{
		Section = TEXT("FromRight");
	}

	PlayHitReactMontage(Section);
}

void ABaseCharacter::PlayHitSound(const FVector& ImpactPoint)
{
	if (HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, ImpactPoint);
	}
}

void ABaseCharacter::SpawnHitParticles(const FVector& ImpactPoint)
{
	if (HitParticles && GetWorld())
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, ImpactPoint);
	}
}

void ABaseCharacter::PlayMontageSection(UAnimMontage* Montage, const FName& SectionName)
{
	if (!Montage) return;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->Montage_Play(Montage);
		AnimInstance->Montage_JumpToSection(SectionName, Montage);
	}
}

const int32 ABaseCharacter::PlayRandomMontageSection(UAnimMontage* Montage, const TArray<FName>& SectionNames)
{
	if (!Montage) return -1;
	if (SectionNames.IsEmpty()) return -1;

	const int32 MaxSectionIndex = SectionNames.Num() - 1;
	const int32 Selection = FMath::RandRange(0, MaxSectionIndex);
	PlayMontageSection(Montage, SectionNames[Selection]);
	return Selection;
}

void ABaseCharacter::DisableCapsule()
{
	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ABaseCharacter::StopAttackMontage()
{
	if (!AttackMontage) return;

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->Montage_Stop(0.25f, AttackMontage);
	}
}

void ABaseCharacter::DisableMeshCollision()
{
	if (GetMesh())
	{
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}
