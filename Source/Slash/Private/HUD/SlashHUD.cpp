// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/SlashHUD.h"
#include "HUD/SlashOverlay.h"

void ASlashHUD::BeginPlay()
{
	Super::BeginPlay();

	if (SlashOverlayClass)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			APlayerController* Controller = World->GetFirstPlayerController();
			if (Controller)
			{
				SlashOverlay = CreateWidget<USlashOverlay>(Controller, SlashOverlayClass);
				if (SlashOverlay)
				{
					SlashOverlay->AddToViewport();
				}
			}
		}
	}
}
