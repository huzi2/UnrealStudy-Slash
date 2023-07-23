// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "Slash/DebugMacros.h"

AItem::AItem()
	: Amplitude(0.25f)
	, TimeConstant(5.f)
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	RootComponent = ItemMesh;
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Begin Play called!"));
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunningTime += DeltaTime;
}

float AItem::TransformSin(float Value) const
{
	return FMath::Sin(Value * TimeConstant) * Amplitude;
}

float AItem::TransformCos(float Value) const
{
	return FMath::Cos(Value * TimeConstant) * Amplitude;
}
