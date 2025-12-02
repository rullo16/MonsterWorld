// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/GameHUD.h"
#include "HUD/GameOverlay.h"

void AGameHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (!World) return;

	APlayerController* Controller = World->GetFirstPlayerController();
	if (!Controller && !GameOverlayClass) return;

	GameOverlay = CreateWidget<UGameOverlay>(Controller, GameOverlayClass);

	if (GameOverlay)
	{
		GameOverlay->AddToViewport();
	}
}
