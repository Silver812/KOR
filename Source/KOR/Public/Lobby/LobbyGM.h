// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/KorBaseGM.h"
#include "LobbyGM.generated.h"

UCLASS()
class KOR_API ALobbyGM : public AKorBaseGM
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

protected:
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
};
