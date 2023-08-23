// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SLASH_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	UAttributeComponent();

private:
	virtual void BeginPlay() override;

public:
	FORCEINLINE const float GetStamina() const { return Stamina; }
	FORCEINLINE const int32 GetGold() const { return Gold; }
	FORCEINLINE const int32 GetSouls() const { return Souls; }
	FORCEINLINE const float GetDodgeCost() const { return DodgeCost; }

	void ReceiveDamage(const float Damage);
	void UseStamina(const float StaminaCost);
	const float GetHealthPercent() const;
	const float GetStaminaPercent() const;
	const bool IsAlive() const;
	void AddGold(const int32 AmountOfGold);
	void AddSouls(const int32 NumberOfSouls);
	void RegenStamina(const float DeltaTime);

private:
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float Health;
	
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float MaxHealth;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float Stamina;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float MaxStamina;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	int32 Gold;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	int32 Souls;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float DodgeCost;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float StaminaRegenRate;
};
