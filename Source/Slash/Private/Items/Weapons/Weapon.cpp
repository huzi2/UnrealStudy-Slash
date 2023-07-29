// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/Weapon.h"

void AWeapon::Equip(USceneComponent* InParent, const FName& InSocketName)
{
	if (ItemMesh && InParent)
	{
		ItemMesh->AttachToComponent(InParent, FAttachmentTransformRules::SnapToTargetIncludingScale, InSocketName);
	}
}

void AWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}
