// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGM.generated.h"

class UKorGMDefinition;

UCLASS()
class KOR_API AMainMenuGM : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GMDefinition")
	TObjectPtr<UKorGMDefinition> GMDefinition;
	
public:
	virtual void BeginPlay() override;
};
