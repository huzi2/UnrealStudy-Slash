// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "CharacterTypes.h"
#include "SlashCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AItem;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class SLASH_API ASlashCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ASlashCharacter();

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	virtual void Attack() override;
	virtual void PlayAttackMontage() override;
	virtual bool CanAttack() const override;
	virtual void AttackEnd() override;

public:
	FORCEINLINE void SetOverlappingItem(AItem* Item) { OverlappingItem = Item; }
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }

private:
	void MoveForward(const FInputActionValue& Value);
	void MoveRight(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	void LookUp(const FInputActionValue& Value);
	void EKeyPressed();

	void PlayEquipMontage(const FName& SectionName);

	UFUNCTION(BlueprintCallable)
	void Disarm();

	UFUNCTION(BlueprintCallable)
	void Arm();

	UFUNCTION(BlueprintCallable)
	void FinishEquipping();

	bool CanDisarm() const;
	bool CanArm() const;

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

private:
	ECharacterState CharacterState;
};
