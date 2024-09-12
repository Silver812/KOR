// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/KorBasePC.h"
#include "Character/KORCharacter.h"
#include "Core/KORGS.h"
#include "GameFramework/SpectatorPawn.h"

void AKorBasePC::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

AKorBasePC::AKorBasePC()
{
	bReplicates = true;
}

void AKorBasePC::SetPlayerColorMaterial(int32 NewPlayerColorIndex)
{
	GetPlayerCharacterRef()->GetMesh()->SetMaterial(CharacterBodyMaterialIndex, PlayerColors[NewPlayerColorIndex]);
}

void AKorBasePC::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AKorBasePC::BeginPlay()
{
	Super::BeginPlay();

	// TODO: complete this in the future, for know it crashes the game
	// SetPlayerColorMaterial(GetKorGI()->PlayerColorIndex);
	SetInputMode(FInputModeGameOnly());
	SetShowMouseCursor(false);
}

void AKorBasePC::Die()
{
	if (IsLocalController())
	{
		ServerSwitchToSpectator();
	}
}

AKORCharacter* AKorBasePC::GetPlayerCharacterRef()
{
	if (!PlayerCharacter)
	{
		PlayerCharacter = Cast<AKORCharacter>(GetPawn());
	}

	return PlayerCharacter;
}

void AKorBasePC::ServerSwitchToSpectator_Implementation()
{
	if (APawn* CurrentPawn = GetPawn())
	{
		FVector Location = CurrentPawn->GetActorLocation() + FVector(0.0f,0.0f,200.0f);
		FRotator Rotation = CurrentPawn->GetActorRotation();
		CurrentPawn->UnPossessed();
		ChangeState(NAME_Spectating);

		if (const AKORGS* GameState = GetWorld()->GetGameState<AKORGS>())
		{
			if (const TSubclassOf<APawn> SpectatorPawnClass = GameState->SpectatorClass)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;

				if (APawn* NewSpectatorPawn = GetWorld()->SpawnActor<APawn>(SpectatorPawnClass, Location, Rotation, SpawnParams))
				{
					Possess(NewSpectatorPawn);
				}
			}
		}
	}
}
