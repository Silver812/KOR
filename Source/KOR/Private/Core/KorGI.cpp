// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/KorGI.h"
#include "Core/KorGMDefTable.h"

void UKorGI::Init()
{
	Super::Init();

	if (GMDefTable)
	{
		GMDefinitionsMap.Empty();
		
		static const FString ContextString(TEXT("DataAssetRow"));
		TArray<FName> RowNames = GMDefTable->GetRowNames();

		for (auto& RowName : RowNames)
		{
			if (const FKorGMDefTable* Row = GMDefTable->FindRow<FKorGMDefTable>(RowName, ContextString))
			{
				GMDefinitionsMap.Add(RowName, Row->GMDefinition);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Game mode definition table not found"));
	}

	// Copy the GMDefinitionsList to the backup
	GMDefinitionsListBackup = GMDefinitionsMap;

	if (PlayerName.IsNone())
	{
		PlayerName = FName(*(TEXT("P") + FString::Printf(TEXT("%d"), FMath::RandRange(0, 100000))));
	}

	if (PlayerColorIndex == -1)
	{
		PlayerColorIndex = FMath::RandRange(0, 7);
	}
}

void UKorGI::PrintGMDefinitionsList() const
{
	for (auto& GMDefinition : GMDefinitionsMap)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
		                                 FString::Printf(TEXT("GM Name: %s"), *GMDefinition.Key.ToString()));
	}
}
