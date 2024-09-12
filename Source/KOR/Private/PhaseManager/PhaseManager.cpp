// Fill out your copyright notice in the Description page of Project Settings.

#include "PhaseManager/PhaseManager.h"

bool UPhaseManager::PopulatePhaseList(const TSubclassOf<UPhase> PhaseClass)
{
	if (PhaseClass)
	{
		if (UPhase* NewPhase = NewObject<UPhase>(this, PhaseClass))
		{
			NewPhase->WorldContext = WorldContext;
			PhaseList.Add(NewPhase);

			// When it creates the phase, it registers the phase OnPhaseFinished. After the phase ends, it broadcasts
			NewPhase->PhaseCompleted.AddLambda([this]() { ActivateNextPhase(true); });
			return true;
		}

		UE_LOG(LogTemp, Warning, TEXT("Failed to create instance of phase class"));
		return false;
	}

	UE_LOG(LogTemp, Warning, TEXT("Invalid phase class provided"));
	return false;
}

bool UPhaseManager::PopulatePhaseList(TArray<TSubclassOf<UPhase>> PhasesArray)
{
	if (PhasesArray.IsEmpty())
	{
		return false;
	}

	for (const auto Element : PhasesArray)
	{
		if (!PopulatePhaseList(Element))
		{
			return false;
		}
	}

	return true;
}

void UPhaseManager::Init(const TArray<TSubclassOf<UPhase>>& Phases, UWorld* _WorldContext)
{
	WorldContext = _WorldContext;
	PopulatePhaseList(Phases);
}


void UPhaseManager::ActivateNextPhase(const bool ShouldPop)
{
	if (ShouldPop and !PhaseList.IsEmpty())
	{
		PhaseList.Pop();
	}

	// Blueprint native Event for the activate Phase
	if (PhaseList.IsEmpty())
	{
		return;
	}

	PhaseList.Top()->OnPhaseActivated();
}
