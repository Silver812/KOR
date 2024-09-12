// Fill out your copyright notice in the Description page of Project Settings.

#include "FloorIsLava/PlatformSpawner.h"
#include "FloorIsLava/FILPlatformStruct.h"
#include "UObject/ConstructorHelpers.h"

UPlatformSpawner::UPlatformSpawner()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPlatformSpawner::BeginPlay()
{
	Super::BeginPlay();
}
FFILPlatformStruct& UPlatformSpawner::GetPlatform(const int Difficulty) const
{
	if (FILPlatformDT)
	{
		// Filter the data table using a lambda predicate
		TArray<FFILPlatformStruct*> FilteredPlatforms;
		static const FString ContextString(TEXT("DataAssetRow"));

		for (TArray<FName> RowNames = FILPlatformDT->GetRowNames(); const auto& RowName : RowNames)
		{
			if (FFILPlatformStruct* Row = FILPlatformDT->FindRow<FFILPlatformStruct>(RowName, ContextString))
			{
				if (Row->Difficulty == Difficulty)
					FilteredPlatforms.Add(Row);
			}
		}
		
		if (FilteredPlatforms.Num() > 0)
		{
			const int32 RandomIndex = FMath::RandRange(0, FilteredPlatforms.Num() - 1);
			// Returns the random platform class
			return *FilteredPlatforms[RandomIndex];
		}
	}
	
	UE_LOG(LogTemp, Error, TEXT("Game mode definition table not found or no platforms match the difficulty"));
	
	// Handle the error appropriately. For example, you might throw an exception, return a default value, or use an error code.
	static FFILPlatformStruct DefaultPlatform;
	return DefaultPlatform;
}