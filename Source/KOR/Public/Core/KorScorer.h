// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameStateComponent.h"
#include "Templates/Tuple.h" // Can't forward declare TTuple
#include "KorScorer.generated.h"

class UScorerAlgorithm;

// Typedef so the macro doesn't get confused
using FScoreArray = const TMap<FName, int32>&;

// Delegate for when the game finishes
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameFinishedSignature, FScoreArray);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KOR_API UKorScorer : public UGameStateComponent
{
	GENERATED_BODY()

	// The scores of the players during the game and the final scores that will be sent to the subsystem when the game finishes
	TMap<FName, int32> PlayerScores;

	// Determines how the scores are calculated
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoring", meta = (AllowPrivateAccess = "true"))
	UScorerAlgorithm* Algorithm;

	// The amount of points that a player needs to win the game. Should be 0 if it is not a win condition
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Scoring", meta = (AllowPrivateAccess = "true"))
	int ScoreLimit;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void InitAlgorithmClass();

	// Sets default values for this component's properties
	UKorScorer(const FObjectInitializer& ObjectInitializer);

	FOnGameFinishedSignature OnGameFinished;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	// Adds a point to the player's score
	UFUNCTION(BlueprintCallable)
	void PlayerScored(FName PlayerName);

	// Called when the game finishes, it sends the data to the permanent scoring subsystem
	UFUNCTION(BlueprintCallable)
	void GameFinished();
};
