// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "ScoreManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMatchFinishedSignature);

USTRUCT()
struct FReplicatedPlayerScore
{
	GENERATED_BODY()

	UPROPERTY()
	FName PlayerName = TEXT("");

	UPROPERTY()
	int32 Score = 0;

	FReplicatedPlayerScore(const FName InPlayerName = TEXT(""), const int32 InScore = 0) : PlayerName(InPlayerName),
		Score(InScore)
	{
	}
};

/**
 * 
 */
UCLASS()
class KOR_API UScoreManager : public ULocalPlayerSubsystem
{
	GENERATED_BODY()

	// Usable Map of player scores
	UPROPERTY()
	TMap<FName, int32> PlayerScores;

	// How many minigames will be played in a match
	UPROPERTY()
	int32 MinigameCounter;

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	void UpdateScores(const TMap<FName, int32>& Scores);

	FOnMatchFinishedSignature OnMatchFinished;

	TMap<FName, int32>& GetPlayerScores() { return PlayerScores; }

	UFUNCTION(BlueprintCallable, Category = "ScoreManager")
	int32 GetMinigameCounter() const { return MinigameCounter; }

	void ResetPlayerScores() { PlayerScores.Empty(); }

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "ScoreManager")
	TArray<FName> GetScores();

	// Call OnRep_PlayerScoresMap on the server
	UFUNCTION()
	void SetPlayerScoresMap(TArray<FReplicatedPlayerScore>& PlayerScoresArray);

	//Debug
	UFUNCTION(BlueprintCallable, Category = "ScoreManager")
	void PrintPlayerScores() const;

	void SetMiniGameCounter(int32 NewCounter) { MinigameCounter = NewCounter; }
};
