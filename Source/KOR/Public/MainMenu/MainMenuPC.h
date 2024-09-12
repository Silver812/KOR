﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuPC.generated.h"

class UInputMappingContext;

UCLASS()
class KOR_API AMainMenuPC : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
};
