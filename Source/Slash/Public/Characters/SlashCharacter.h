// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterTypes.h"
#include "SlashCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AItem;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class SLASH_API ASlashCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASlashCharacter();

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	FORCEINLINE void SetOverlappingItem(AItem* Item) { OverlappingItem = Item; }
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }

private:
	void MoveForward(const FInputActionValue& Value);
	void MoveRight(const FInputActionValue& Value);
	void Turn(const FInputActionValue& Value);
	void LookUp(const FInputActionValue& Value);
	void EKeyPressed();

private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;

	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;

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

private:
	ECharacterState CharacterState;
};
