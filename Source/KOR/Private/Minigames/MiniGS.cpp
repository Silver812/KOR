// Fill out your copyright notice in the Description page of Project Settings.

#include "Minigames/MiniGS.h"
#include "Core/KorScorer.h"
#include "Core/ScoreManager.h"
#include "Net/UnrealNetwork.h"
#include "Net/Core/PushModel/PushModel.h"

void AMiniGS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AMiniGS, ReplicatedPlayerScores);
}

void AMiniGS::ReplicateMap(const TMap<FName, int32>& PlayerScores)
{
	// If we are the server, replicate the map to all clients
	if (HasAuthority())
	{
		ReplicatedPlayerScores.Reset();
		const TArray<TPair<FName, int32>>& PlayerScoresArray = PlayerScores.Array();
		
		for (auto& PlayerScore : PlayerScoresArray)
		{
			FReplicatedPlayerScore RepPlayerScore(PlayerScore.Key, PlayerScore.Value);
			ReplicatedPlayerScores.Add(MoveTemp(RepPlayerScore));
		}

		MARK_PROPERTY_DIRTY_FROM_NAME(AMiniGS, ReplicatedPlayerScores, this);
	}
}

void AMiniGS::OnRep_PlayerScoresMap()
{
	// Update the match score in the ScoreManager subsystem
	if (const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController())
	{
		if (UScoreManager* ScoreManager = LocalPlayer->GetSubsystem<UScoreManager>())
		{
			ScoreManager->SetPlayerScoresMap(ReplicatedPlayerScores);
		}
	}
}

AMiniGS::AMiniGS() : Super()
{
	// If we are the server, create the scorer
	if (HasAuthority())
	{
		Scorer = CreateDefaultSubobject<UKorScorer>(TEXT("Scorer"));
	}
}
