// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScorerAlgorithm.h"
#include "LastInWinner.generated.h"

UCLASS()
class KOR_API ULastInWinner : public UScorerAlgorithm
{
	GENERATED_BODY()

public:
	ULastInWinner() : UScorerAlgorithm(0, -1)
	{
	}

	virtual void Score(TMap<FName, int32>& PlayerScores) override;
};