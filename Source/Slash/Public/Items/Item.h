// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class USphereComponent;
class UNiagaraComponent;

enum class EItemState : uint8
{
	EIS_Hovering,
	EIS_Equipped
};

UCLASS()
class SLASH_API AItem : public AActor
{
	GENERATED_BODY()
	
protected:
	AItem();

protected:
	virtual void BeginPlay() override;

private:
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintPure)
	float TransformSin() const;

	UFUNCTION(BlueprintPure)
	float TransformCos() const;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
	float Amplitude;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
	float TimeConstant;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ItemMesh;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere;

	UPROPERTY(EditAnywhere)
	UNiagaraComponent* ItemEffect;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float RunningTime;

protected:
	EItemState ItemState;
};
