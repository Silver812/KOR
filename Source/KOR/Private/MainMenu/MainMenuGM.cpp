// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenu/MainMenuGM.h"
#include "Core/KorGI.h"
#include "Core/KorGMDefinition.h"
#include "Core/ScoreManager.h"
#include "Kismet/GameplayStatics.h"

void AMainMenuGM::BeginPlay()
{
	Super::BeginPlay();
	
	// Assign a random name to the player
	if (UKorGI* KorGI = Cast<UKorGI>(GetGameInstance()))
	{
		// Reset systems
		KorGI->ResetGMDefinitionsList();

		// Find the GMDefinition (data asset) inside GMDefinitionsList that corresponds to the current map
		for (const TTuple<FName, TObjectPtr<UKorGMDefinition>>& GMDef : KorGI->GMDefinitionsMap)
		{
			if (GMDef.Value->Level.GetAssetName() == UGameplayStatics::GetCurrentLevelName(GetWorld()))
			{
				GMDefinition = GMDef.Value;

				// Get ScoreManager subsystem
				if (const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController())
				{
					if (UScoreManager* ScoreManager = LocalPlayer->GetSubsystem<UScoreManager>())
					{
						ScoreManager->SetMiniGameCounter(GMDefinition->NumberOfMinigames);
					}
				}
				
				break;
			}
		}
		
		if (const ULocalPlayer* LocalPlayer = GetWorld()->GetFirstLocalPlayerFromController())
		{
			if (UScoreManager* ScoreManager = LocalPlayer->GetSubsystem<UScoreManager>())
			{
				ScoreManager->ResetPlayerScores();
			}
		}
	}
}
