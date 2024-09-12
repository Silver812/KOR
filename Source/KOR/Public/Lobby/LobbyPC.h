// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/KorBasePC.h"
#include "LobbyPC.generated.h"

UCLASS()
class KOR_API ALobbyPC : public AKorBasePC
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
};
