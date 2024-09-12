// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/KorBasePS.h"
#include "Core/KorGI.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

void AKorBasePS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(AKorBasePS, PlayerName);
	DOREPLIFETIME(AKorBasePS, PlayerColorIndex);
}


void AKorBasePS::BeginPlay()
{
	Super::BeginPlay();

	if (UGameplayStatics::GetPlayerController(GetWorld(),0) == GetPlayerController())
	{
		SetPlayerName_Server(GetKorGI()->PlayerName);
		// SetPlayerName(GetKorGI()->PlayerName.ToString());
		// UE_LOG(LogTemp,Display,TEXT("%s"),*GetKorGI()->PlayerName.ToString());
		// SetPlayerColor_Server(GetKorGI()->PlayerColorIndex);
	}
}

void AKorBasePS::SetPlayerColor_Server_Implementation(int32 NewPlayerColorIndex)
{
	PlayerColorIndex = NewPlayerColorIndex;
}

void AKorBasePS::SetPlayerName_Server_Implementation(FName NewPlayerName)
{
	PlayerName = NewPlayerName;
}

void AKorBasePS::OnRep_PlayerColorIndex()
{
	// The material of the player body is 2.
	// SetPlayerColorMaterial(PlayerColorIndex);
}

UKorGI* AKorBasePS::GetKorGI() 
{
	if(KorGI == nullptr)
	{
		KorGI = Cast<UKorGI>(GetGameInstance());
	}
	
	return KorGI;
}
