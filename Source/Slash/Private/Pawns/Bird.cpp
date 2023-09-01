// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/Bird.h"
#include "Components/CapsuleComponent.h"
#include "GameFrameWork/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"

ABird::ABird()
{
	PrimaryActorTick.bCanEverTick = false;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetCapsuleHalfHeight(20.f);
	Capsule->SetCapsuleRadius(15.f);
	SetRootComponent(Capsule);

	BridMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BridMesh"));
	BridMesh->SetupAttachment(GetRootComponent());

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom);

	DefaultInputMappingContext = CreateDefaultSubobject<UInputMappingContext>(TEXT("DefaultInputMappingContext"));
	MoveForwardInputAction = CreateDefaultSubobject<UInputAction>(TEXT("MoveForwardInputAction"));
	TurnInputAction = CreateDefaultSubobject<UInputAction>(TEXT("TurnInputAction"));
	LookUpInputAction = CreateDefaultSubobject<UInputAction>(TEXT("LookUpInputAction"));

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void ABird::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultInputMappingContext, 0);
		}
	}
}

void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(MoveForwardInputAction, ETriggerEvent::Triggered, this, &ABird::MoveForward);
		Input->BindAction(TurnInputAction, ETriggerEvent::Triggered, this, &ABird::Turn);
		Input->BindAction(LookUpInputAction, ETriggerEvent::Triggered, this, &ABird::LookUp);
	}
}

void ABird::MoveForward(const FInputActionValue& Value)
{
	const float MovementValue = Value.Get<float>();

	if (Controller && MovementValue != 0.f)
	{
		FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, MovementValue);
	}
}

void ABird::Turn(const FInputActionValue& Value)
{
	const float MovementValue = Value.Get<float>();
	
	AddControllerYawInput(MovementValue);
}

void ABird::LookUp(const FInputActionValue& Value)
{
	const float MovementValue = Value.Get<float>();

	AddControllerPitchInput(MovementValue);
}
