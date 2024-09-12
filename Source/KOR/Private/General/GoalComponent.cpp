// Fill out your copyright notice in the Description page of Project Settings.

#include "General/GoalComponent.h"
#include "Core/KorBasePS.h"
#include "Core/KorScorer.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerState.h"

// Sets default values for this component's properties
UGoalComponent::UGoalComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGoalComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UGoalComponent::OnOverlapBegin);

	// Set KorScorer
	Scorer = Cast<UKorScorer>(GetWorld()->GetGameState()->GetComponentByClass(UKorScorer::StaticClass()));
}


// Called every frame
void UGoalComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UGoalComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp,
                                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const AActor* Owner = GetOwner();

	// If we are the server
	if (Owner && Owner->HasAuthority())
	{
		const ACharacter* OtherActorChar = Cast<ACharacter>(OtherActor);
		const AKorBasePS* PlayerPS = Cast<AKorBasePS>(OtherActorChar->GetPlayerState());
		
		// Check if the overlapped actor is a ACharacter and is not in the map
		if (OtherActorChar and !FinishedPlayers.Contains(PlayerPS->GetPlayerNameKor()))
		{
			// Add a point to the player's score
			Scorer->PlayerScored(PlayerPS->GetPlayerNameKor());

			// Add the player to the map
			FinishedPlayers.Add(PlayerPS->GetPlayerNameKor(), 1);
		}
	}
}
