// Fill out your copyright notice in the Description page of Project Settings.

#include "Minigames/MiniGM.h"

#include "Components/AudioComponent.h"
#include "Core/KorScorer.h"
#include "Kismet/GameplayStatics.h"
#include "Minigames/MiniGS.h"
#include "PhaseManager/PhaseManager.h"
#include "Sound/AmbientSound.h"

void AMiniGM::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		if (const AMiniGS* GS = GetGameState<AMiniGS>())
		{
			// Bind EndMinigame to the OnGameFinished from the scorer
			GS->Scorer->OnGameFinished.AddUObject(this, &ThisClass::EndMinigame);
		}
	}
}

void AMiniGM::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);
}

void AMiniGM::EndMinigame(const TMap<FName, int32>& PlayerScores) const
{
	UE_LOG(LogTemp, Display, TEXT("Minigame ended, going back to the lobby"));
	PhaseManager->ActivateNextPhase(true);

	// Get all objets with tag
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), MusicTag, FoundActors);

	if (!FoundActors.IsEmpty())
	{
		// Cast to Ambient Sound (MetaSound Source)
		if (const AAmbientSound* AmbientSound = Cast<AAmbientSound>(FoundActors[0]))
		{
			// Execute Trigger Parameter
			AmbientSound->GetAudioComponent()->SetTriggerParameter(SectionNameTag);
		}
	}
}
