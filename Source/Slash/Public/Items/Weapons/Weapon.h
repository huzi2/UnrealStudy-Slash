// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Weapon.generated.h"

class UBoxComponent;
/**
 * 
 */
UCLASS()
class SLASH_API AWeapon : public AItem
{
	GENERATED_BODY()

private:
	AWeapon();

private:
	virtual void BeginPlay() final;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void CreateFields(const FVector& FieldLocation);

private:
	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	FORCEINLINE UBoxComponent* GetWeaponBox() const { return WeaponBox; }

	void Equip(USceneComponent* InParent, const FName& InSocketName, AActor* NewOwner, APawn* NewInstigator);
	void AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName);

private:
	const bool ActorIsSameType(AActor* OtherActor) const;
	void PlayEquipSound();
	void DisableSphereCollision();
	void DeactivateEmbers();
	void BoxTrace(FHitResult& BoxHit);
	void ExecuteGetHit(const FHitResult& BoxHit);

private:
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	USoundBase* EquipSound;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	UBoxComponent* WeaponBox;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* BoxTraceStart;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* BoxTraceEnd;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	FVector BoxTraceExtent;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	bool bShowBoxDebug;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	float Damage;

public:
	TArray<AActor*> IgnoreActors;
};
