// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Interfaces/PickupInterface.h"
#include "SlashCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class USlashOverlay;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class SLASH_API ASlashCharacter : public ABaseCharacter, public IPickupInterface
{
	GENERATED_BODY()

public:
	ASlashCharacter();

private:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Jump() override;

private:
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;
	virtual void SetOverlappingItem(AItem* Item) override;
	virtual void AddGold(ATreasure* Treasure) override;
	virtual void AddSouls(ASoul* Soul) override;

private:
	virtual const bool CanAttack() const override;

	virtual void Attack() override;
	virtual void AttackEnd() override;
	virtual void DodgeEnd() override;
	virtual void Die_Implementation() override;

public:
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
	FORCEINLINE EActionState GetActionState() const { return ActionState; }

private:
	UFUNCTION(BlueprintCallable)
	void AttachWeaponToBack();

	UFUNCTION(BlueprintCallable)
	void AttachWeaponToHand();

	UFUNCTION(BlueprintCallable)
	void FinishEquipping();

	UFUNCTION(BlueprintCallable)
	void HitReactEnd();

private:
	const bool CanDisarm() const;
	const bool CanArm() const;
	const bool IsUnoccupied() const;
	const bool HasEnoughStamina() const;

	void MoveForward(const FInputActionValue& Value);
	void MoveRight(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	void LookUp(const FInputActionValue& Value);
	void EKeyPressed();
	void PlayEquipMontage(const FName& SectionName);
	void EquipWeapon(AWeapon* Weapon);
	void DisArm();
	void Arm();
	void Dodge();

	void InitializeSlashOverlay();
	void SetHUDHealth();

private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;

	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* EquipMontage;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EActionState ActionState;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* DefaultInputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveForwardInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveRightInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* TurnInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookUpInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* EquipInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* AttackInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* DodgeInputAction;

	UPROPERTY()
	USlashOverlay* SlashOverlay;

private:
	ECharacterState CharacterState;
};
