// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/KORGS.h"
#include "MiniGS.generated.h"

struct FReplicatedPlayerScore;
class UKorScorer;

UCLASS()
class KOR_API AMiniGS : public AKORGS
{
	GENERATED_BODY()
	
	UPROPERTY(ReplicatedUsing=OnRep_PlayerScoresMap)
	TArray<FReplicatedPlayerScore> ReplicatedPlayerScores;

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoring")
	UKorScorer* Scorer;

	void ReplicateMap(const TMap<FName, int32>& PlayerScores);
	
	UFUNCTION()
	void OnRep_PlayerScoresMap();

	AMiniGS();
};
