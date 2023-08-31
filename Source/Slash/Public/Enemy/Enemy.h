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
	virtual void BeginPlay() final;
	virtual void Tick(float DeltaTime) final;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) final;
	virtual void Destroyed() final;

private:
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) final;

private:
	virtual bool CanAttack() const final;

	virtual void Attack() final;
	virtual void AttackEnd() final;
	virtual void Die_Implementation() final;
	virtual void HandleDamage(const float DamageAmount) final;

private:
	UFUNCTION()
	void PawnSee(APawn* SeenPawn);

private:
	bool InTargetRange(AActor* Target, const double Radius) const;
	bool IsOutsideCombatRadius() const;
	bool IsOutsideAttackRadius() const;
	bool IsInsideAttackRadius() const;
	bool IsChasing() const;
	bool IsAttacking() const;
	bool IsDead() const;
	bool IsEngaged() const;

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
