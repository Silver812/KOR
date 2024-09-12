// Fill out your copyright notice in the Description page of Project Settings.

#include "Minigames/ScorerAlgorithm.h"
#include "Core/KorBaseGM.h"
#include "Core/KorGMDefinition.h"
#include "Kismet/GameplayStatics.h"

UScorerAlgorithm::UScorerAlgorithm(const int32 InCount, const int32 InCountAdvancer) : Count(InCount), CountAdvancer(InCountAdvancer)
{
	MaxScore = 0;

	if (const UWorld* World = UObject::GetWorld())
	{
		if (const AKorBaseGM* GM = Cast<AKorBaseGM>(UGameplayStatics::GetGameMode(World)))
		{
			MaxScore = GM->GetGMDefinition()->MaxScore;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Can't assign a MaxScore to the ScorerAlgorithm"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("World context object in the ScorerAlgorithm is null. Ignore this if this the CDO"));
	}
}
