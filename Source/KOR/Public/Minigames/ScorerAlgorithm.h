// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ScorerAlgorithm.generated.h"

UCLASS()
class KOR_API UScorerAlgorithm : public UObject
{
	GENERATED_BODY()

protected:
	// Maximum amount of points that will be awarded to the winner of this minigame
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoring", meta = (AllowPrivateAccess = "true"))
	int32 MaxScore;
	int32 Count;
	int32 CountAdvancer;

public:
	UScorerAlgorithm() = default;
	UScorerAlgorithm(const int32 InCount, const int32 InCountAdvancer);

	// Assigns a final score to each player
	virtual void Score(TMap<FName, int32>& PlayerScore)
	{
	}
};
