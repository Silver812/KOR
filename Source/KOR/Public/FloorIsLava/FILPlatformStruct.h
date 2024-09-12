// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlatformBase.h"
#include "FILPlatformStruct.generated.h"

UENUM(BlueprintType)
enum class ESpawnPosition : uint8
{
	CENTER UMETA(DisplayName = "Center"),
	RANDOM UMETA(DisplayName = "Random"),
	COUNT
};

USTRUCT()
struct FFILPlatformStruct : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APlatformBase> PlatformClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ESpawnPosition SpawnPosition = ESpawnPosition::CENTER;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Difficulty = 0;
};
