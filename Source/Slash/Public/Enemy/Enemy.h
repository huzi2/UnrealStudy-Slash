// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Characters/CharacterTypes.h"
#include "Enemy.generated.h"

class UHealthBarComponent;
class AAIController;
class UPawnSensingComponent;

UCLASS()
class SLASH_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()

private:
	AEnemy();

public:
	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Destroyed() override;

private:
	virtual const bool CanAttack() const override;

	virtual void Attack() override;
	virtual void AttackEnd() override;
	virtual void Die() override;
	virtual void HandleDamage(const float DamageAmount) override;
	virtual const int32 PlayDeathMontage() override;

private:
	UFUNCTION()
	void PawnSee(APawn* SeenPawn);

private:
	const bool InTargetRange(AActor* Target, double Radius) const;
	const bool IsOutsideCombatRadius() const;
	const bool IsOutsideAttackRadius() const;
	const bool IsInsideAttackRadius() const;
	const bool IsChasing() const;
	const bool IsAttacking() const;
	const bool IsDead() const;
	const bool IsEngaged() const;

	void CheckCombatTarget();
	void CheckPatrolTarget();
	void ClearPatrolTimer();
	void MoveToTarget(AActor* Target);
	AActor* ChoosePatrolTarget() const;
	void PatrolTimerFinished();
	void HideHealthBar();
	void ShowHealthBar();
	void LoseInterest();
	void StartPatrolling();
	void ChaseTarget();
	void StartAttackTimer();
	void ClearAttackTimer();

protected:
	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EDeathPose> DeathPose;

	UPROPERTY(BlueprintReadOnly)
	EEnemyState EnemyState;

private:
	UPROPERTY(VisibleAnywhere)
	UHealthBarComponent* HealthBarWidget;

	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensing;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> WeaponClass;

	UPROPERTY()
	AActor* CombatTarget;
	
	UPROPERTY(EditAnywhere)
	double CombatRadius;

	UPROPERTY(EditAnywhere)
	double AttackRadius;

	UPROPERTY(EditAnywhere)
	double PatrolRadius;

	UPROPERTY()
	AAIController* EnemyController;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	AActor* PatrolTarget;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	TArray<AActor*> PatrolTargets;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float WaitMin;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float WaitMax;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float PatrollingSpeed;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float ChasingSpeed;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackMin;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackMax;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float DeathLifeSpan;

private:
	FTimerHandle PatrolTimer;
	FTimerHandle AttackTimer;
};
