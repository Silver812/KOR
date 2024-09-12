// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScorerAlgorithm.h"
#include "FirstInWinner.generated.h"

UCLASS()
class KOR_API UFirstInWinner : public UScorerAlgorithm
{
	GENERATED_BODY()

public:
	// Calls the constructor of the parent class
	UFirstInWinner() : UScorerAlgorithm(0, 1)
	{
	}

	virtual void Score(TMap<FName, int32>& PlayerScores) override;
};
