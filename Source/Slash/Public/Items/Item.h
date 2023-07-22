// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class SLASH_API AItem : public AActor
{
	GENERATED_BODY()
	
private:
	AItem();

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	float RunningTime;
	float Amplitude;
	float TimeConstant;
};
