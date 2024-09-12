// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KORBaseUserWidget.generated.h"

class AKORBaseHUD;

UCLASS()
class KOR_API UKORBaseUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	AKORBaseHUD* HUD;
	
	UFUNCTION(Blueprintable,BlueprintPure)
	AKORBaseHUD* GetHUD();
};
