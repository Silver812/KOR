// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/ScoreManager.h"
#include "Minigames/MiniGS.h"

void UScoreManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	MinigameCounter = 4;
}

void UScoreManager::Deinitialize()
{
	Super::Deinitialize();
}

void UScoreManager::UpdateScores(const TMap<FName, int32>& Scores)
{
	if (const ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (APlayerController* PlayerController = LocalPlayer->GetPlayerController(GetWorld()))
		{
			// The player controller has authority
			if (PlayerController->HasAuthority())
			{
				// If this is the first minigame, initialize the player scores
				if (PlayerScores.IsEmpty())
				{
					PlayerScores = Scores;
				}
				else
				{
					// Update the player scores
					for (auto& Player : Scores)
					{
						PlayerScores[Player.Key] += Player.Value;
					}
				}

				// Send the map to the Scorer and then replicate it to all clients from there
				GetWorld()->GetGameState<AMiniGS>()->ReplicateMap(PlayerScores);

				MinigameCounter--;

				// If the match is finished...
				if (MinigameCounter == 0)
				{
					OnMatchFinished.Broadcast();
				}
			}
		}
	}
}

void UScoreManager::PrintPlayerScores() const
{
	for (auto PlayerScore : PlayerScores)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
		                                 FString::Printf(
			                                 TEXT("Player: %s, Score: %d"), *PlayerScore.Key.ToString(),
			                                 PlayerScore.Value));
	}
}

TArray<FName> UScoreManager::GetScores()
{
	// Sort the player scores from highest to lowest
	PlayerScores.ValueSort([](const int32 A, const int32 B) { return A > B; });

	TArray<FName> SortedPlayerScores;

	for (auto& PlayerScore : PlayerScores)
	{
		// Combine PlayerScore Key and Value into a single FName and add it to the array
		SortedPlayerScores.
			Add(FName(*(PlayerScore.Key.ToString() + FString::Printf(TEXT(" | %d"), PlayerScore.Value))));
	}

	return SortedPlayerScores;
}

void UScoreManager::SetPlayerScoresMap(TArray<FReplicatedPlayerScore>& PlayerScoresArray)
{
	PlayerScores.Reset();

	for (const FReplicatedPlayerScore& RepMapEntry : PlayerScoresArray)
	{
		PlayerScores.Emplace(RepMapEntry.PlayerName, RepMapEntry.Score);
	}

	UE_LOG(LogTemp, Warning, TEXT("Player scores replicated"));
}
