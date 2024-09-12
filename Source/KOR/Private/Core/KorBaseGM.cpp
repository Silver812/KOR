// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/KorBaseGM.h"
#include "Character/KORCharacter.h"
#include "Character/KORSpectator.h"
#include "Core/KorBasePC.h"
#include "Core/KorGI.h"
#include "Core/KorGMDefinition.h"
#include "Core/KORGS.h"
#include "GameFramework/GameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "PhaseManager/PhaseManager.h"

void AKorBaseGM::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	bool GMDefinitionFound = false;
	
	// Load GMDefinition
	if (UKorGI* GameInstance = Cast<UKorGI>(GetGameInstance()))
	{
		// Find the GMDefinition (data asset) inside GMDefinitionsList that corresponds to the current map
		for (const TTuple<FName, TObjectPtr<UKorGMDefinition>>& GMDef : GameInstance->GMDefinitionsMap)
		{
			if (GMDef.Value->Level.GetAssetName() == UGameplayStatics::GetCurrentLevelName(GetWorld()))
			{
				GMDefinition = GMDef.Value;
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, GMDefinition->GetFName().ToString());
				GMDefinitionFound = true;
				break;
			}
		}
	}

	if (!GMDefinitionFound)
	{
		GEngine->AddOnScreenDebugMessage( -1, 5.f, FColor::Red, TEXT("GMDefinition not found") );
	}
}

AKorBaseGM::AKorBaseGM()
{
	GameStateClass = AKORGS::StaticClass();
	SpectatorClass = AKORSpectator::StaticClass();
}

void AKorBaseGM::InitGameState()
{
	Super::InitGameState();
	
	if (AKORGS* CustomGameState = GetGameState<AKORGS>())
	{
		CustomGameState->NewSpectatorClass = SpectatorClass;
	}
}
void AKorBaseGM::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("Begin play multiplayer game mode"))

	// Set up the phase manager with the phases inside the data asset
	if (GMDefinition)
	{
		PhaseManager = NewObject<UPhaseManager>(this);
		PhaseManager->Init(GMDefinition->Phases, GetWorld());

		if (PhaseManager)
		{
			// OnAddPlayersCompleted.AddLambda([this]() { PhaseManager->ActivateNextPhase(false); });
			PhaseManager->ActivateNextPhase(false);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Invalid Phase manager class provided"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Game mode definition not found"));
	}
	
	Super::BeginPlay();
}

UKorGMDefinition* AKorBaseGM::GetGMDefinition() const
{
	//Convert TObjectPtr to pointer and return
	return GMDefinition.Get();
}

TArray<APlayerController*> AKorBaseGM::GetPlayerControllers() const
{
	return PlayerControllers;
}

void AKorBaseGM::AllPlayersAdded()
{
	OnAddPlayersCompleted.Broadcast();
}

void AKorBaseGM::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	UE_LOG(LogTemp, Warning, TEXT("New player added"));
	
	PlayerControllers.Add(NewPlayer);
	OnPlayerJoined.Broadcast(NewPlayer);
	
	if (GetGameState<AGameStateBase>()->PlayerArray.Num() == Cast<UKorGI>(GetGameInstance())->Session.MaxPlayers)
	{
		AllPlayersAdded();
		bAllPlayersAdded = true;
	}
}

void AKorBaseGM::CreatePawnForPlayerController(APlayerController* PC)
{
	AKorBasePC* CustomPC = Cast<AKorBasePC>(PC);

	if (!CustomPC->PlayerPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("PC has not a pawn yet"));
		const UKorGI* CustomGI = Cast<UKorGI>(CustomPC->GetGameInstance());
		CustomPC->PlayerPawn = CustomGI->PlayerPawn;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Pc uses previous pawn"));
	}

	const AActor* PlayerStart = FindPlayerStart(PC);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = PC;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	FTransform Transform;
	Transform.SetLocation(PlayerStart->GetActorLocation());
	
	APawn* NewPawn = GetWorld()->SpawnActor<APawn>(CustomPC->PlayerPawn, PlayerStart->GetActorLocation(),
	                                               PlayerStart->GetActorRotation(), SpawnParameters);

	AKORCharacter* KORCharacter = GetWorld()->SpawnActorDeferred<AKORCharacter>(CustomPC->PlayerPawn,Transform,PC);
	
	if(KORCharacter)
	{
		KORCharacter->PlayerNameCustom = Cast<UKorGI>(CustomPC->GetGameInstance())->PlayerName;
		UGameplayStatics::FinishSpawningActor(KORCharacter,Transform);
	}
	
	PC->Possess(KORCharacter);
	PC->Possess(NewPawn);
}

void AKorBaseGM::ChangeToNewSceneServerListen(const TSoftObjectPtr<UWorld>& Level)
{
	ChangeToNewSceneServerListenPath(Level.GetLongPackageName());
}

void AKorBaseGM::ChangeToNewSceneServerListenPath(const FString& LevelPath)
{
	bUseSeamlessTravel = true;
	GetWorld()->ServerTravel(FString::Printf(TEXT("%s?listen"), *LevelPath));
}
