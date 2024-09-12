// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScorerAlgorithm.h"
#include "PointBasedMaxWinner.generated.h"

UCLASS()
class KOR_API UPointBasedMaxWinner : public UScorerAlgorithm
{
	GENERATED_BODY()

public:
	// Calls the constructor of the parent class
	UPointBasedMaxWinner() : UScorerAlgorithm(0, 1)
	{
	}

	virtual void Score(TMap<FName, int32>& PlayerScores) override;
};