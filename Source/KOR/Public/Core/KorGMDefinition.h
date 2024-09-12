// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KORBaseHUD.h"
#include "Engine/DataAsset.h"
#include "Minigames/ScorerAlgorithm.h"
#include "PhaseManager/Phase.h"
#include "KorGMDefinition.generated.h"

/**
 * 
 */
UCLASS()
class KOR_API UKorGMDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UKorGMDefinition() = default;

	// Time limit
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Gameplay)
	int32 TimeLimit;

	// Score limit for the minigame (in the case that it needs one)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Gameplay)
	int32 ScoreLimit;

	// Score awarded to the winner of the minigame
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Gameplay)
	int32 MaxScore;

	// Number of players
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Gameplay)
	int32 MaxPlayerNum;

	// Number of minigames that will be played in a match
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Gameplay)
	int32 NumberOfMinigames;
	
	// Point assignment class in charge of keeping track of the score
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Gameplay)
	TSubclassOf<UScorerAlgorithm> AlgorithmClass;

	// Array of compatible levels (maps) with this game mode
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Level)
	TSoftObjectPtr<UWorld> Level;

	// Array of phases
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UPhase>> Phases;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=UI)
	TSubclassOf<UUserWidget> UIBase;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=UI)
	EInputMode InputModeBase;

	void SetLevel(const TSoftObjectPtr<UWorld>& InLevel) { Level = InLevel; }
};
