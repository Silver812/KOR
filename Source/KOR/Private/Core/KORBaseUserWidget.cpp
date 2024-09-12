// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/KORBaseUserWidget.h"
#include "Core/KORBaseHUD.h"
#include "Kismet/GameplayStatics.h"

AKORBaseHUD* UKORBaseUserWidget::GetHUD()
{
	if(!HUD)
	{
		const APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(),0);
		HUD = Cast<AKORBaseHUD>(PC->GetHUD());
	}
	
	return HUD;
}
