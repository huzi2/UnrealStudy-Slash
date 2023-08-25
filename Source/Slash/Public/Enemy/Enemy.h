// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Enemy.generated.h"

class UHealthBarComponent;
class AAIController;
class UPawnSensingComponent;
class ASoul;

UCLASS()
class SLASH_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()

private:
	AEnemy();

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Destroyed() override;

private:
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;

private:
	virtual const bool CanAttack() const override;

	virtual void Attack() override;
	virtual void AttackEnd() override;
	virtual void Die_Implementation() override;
	virtual void HandleDamage(const float DamageAmount) override;

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

	void InitializeEnemy();
	void SpawnDefaultWeapon();
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
	void SpawnSoul();

protected:
	UPROPERTY(BlueprintReadOnly)
	EEnemyState EnemyState;

private:
	UPROPERTY(VisibleAnywhere)
	UHealthBarComponent* HealthBarWidget;

	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensing;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<AWeapon> WeaponClass;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	double CombatRadius;

	UPROPERTY(EditAnywhere, Category = "Combat")
	double AttackRadius;

	UPROPERTY(EditAnywhere, Category = "Combat")
	double AcceptanceRadius;

	UPROPERTY(EditAnywhere)
	double PatrolRadius;

	UPROPERTY()
	AAIController* EnemyController;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	AActor* PatrolTarget;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	TArray<AActor*> PatrolTargets;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolWaitMin;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolWaitMax;

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

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<ASoul> SoulClass;

private:
	FTimerHandle PatrolTimer;
	FTimerHandle AttackTimer;
};
