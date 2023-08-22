// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SlashAnimInstance.h"
#include "Characters/SlashCharacter.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void USlashAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	SlashCharacter = Cast<ASlashCharacter>(TryGetPawnOwner());
	if (SlashCharacter)
	{
		SlashCharacterMovement = SlashCharacter->GetCharacterMovement();
	}
}

void USlashAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (SlashCharacterMovement && SlashCharacter)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(SlashCharacterMovement->Velocity);
		bIsFalling = SlashCharacterMovement->IsFalling();
		CharacterState = SlashCharacter->GetCharacterState();
		ActionState = SlashCharacter->GetActionState();
		DeathPose = SlashCharacter->GetDeathPose();
	}
}
