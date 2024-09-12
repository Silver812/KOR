// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu/MainMenuPC.h"

void AMainMenuPC::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameAndUI());
	SetShowMouseCursor(true);
}
