// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/KorScorer.h"
#include "Core/KorBaseGM.h"
#include "Core/KorBasePS.h"
#include "Core/KorGMDefinition.h"
#include "Core/ScoreManager.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Minigames/ScorerAlgorithm.h"

// Sets default values for this component's properties
UKorScorer::UKorScorer(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UKorScorer::BeginPlay()
{
	Super::BeginPlay();
}

void UKorScorer::InitAlgorithmClass()
{
	if (const UWorld* World = GetWorld())
	{
		if (const AKorBaseGM* GameMode = Cast<AKorBaseGM>(UGameplayStatics::GetGameMode(World)))
		{
			if (const TSubclassOf<UScorerAlgorithm> AlgorithmClass = GameMode->GetGMDefinition()->AlgorithmClass)
			{
				// Create the algorithm based on the game mode definition
				Algorithm = NewObject<UScorerAlgorithm>(this, AlgorithmClass);

				// Set the score limit
				ScoreLimit = GameMode->GetGMDefinition()->ScoreLimit;
			}
			else
			{
				GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, TEXT("Algorithm class not found") );
			}
		}
	}
}

// Called every frame
void UKorScorer::TickComponent(const float DeltaTime, const ELevelTick TickType,
                               FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UKorScorer::PlayerScored(const FName PlayerName)
{
	/* ADD POINT */

	if (PlayerScores.Contains(PlayerName))
	{
		PlayerScores[PlayerName]++;
	}
	else
	{
		PlayerScores.Add(PlayerName, 1);
	}

	UE_LOG(LogTemp, Display, TEXT("%s scored!"), *PlayerName.ToString());

	/* CHECK IF THE GAME IS OVER */

	// If this game is point based
	if (ScoreLimit > 0)
	{
		// Check if the player has reached the score limit to win the game
		if (PlayerScores[PlayerName] >= ScoreLimit)
		{
			GameFinished();
		}
	}
	// If the number of players in the Map is the same as the number of players in the game, everyone finished
	else if (PlayerScores.Num() == GetWorld()->GetGameState()->PlayerArray.Num())
	{
		GameFinished();
	}
}

void UKorScorer::GameFinished()
{
	UE_LOG(LogTemp, Warning, TEXT("Game Finished"));

	// Check if all the players in the session have scored (case when the match finished before all players scored)
	if (PlayerScores.Num() != GetWorld()->GetGameState()->PlayerArray.Num())
	{
		// Add the remaining players to the scores
		for (const APlayerState* Player : GetWorld()->GetGameState()->PlayerArray)
		{
			const AKorBasePS* PlayerPS = Cast<AKorBasePS>(Player);
			
			if (Player && !PlayerScores.Contains(PlayerPS->GetPlayerNameKor()))
			{
				PlayerScores.Add(PlayerPS->GetPlayerNameKor(), 0);
			}
		}
	}

	// Calculate the final scores
	Algorithm->Score(PlayerScores);

	// Update the match score in the ScoreManager subsystem
	if (const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController())
	{
		if (UScoreManager* ScoreManager = LocalPlayer->GetSubsystem<UScoreManager>())
		{
			ScoreManager->UpdateScores(PlayerScores);
		}
	}

	// Broadcast the final scores
	OnGameFinished.Broadcast(PlayerScores);
}
