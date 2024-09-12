// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PhaseManager/Phase.h"
#include "PhaseManager.generated.h"

DECLARE_MULTICAST_DELEGATE(FAllPhasesCompleted)

UCLASS(Blueprintable)
class KOR_API UPhaseManager : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<UPhase*> PhaseList;

public:
	UPhaseManager() = default;
	UFUNCTION(BlueprintCallable)
	void ActivateNextPhase(bool ShouldPop = true);
	void Init(const TArray<TSubclassOf<UPhase>>& Phases, UWorld* _WorldContext);

protected:
	UPROPERTY()
	UWorld* WorldContext;

	bool PopulatePhaseList(const TSubclassOf<UPhase> PhaseClass);
	bool PopulatePhaseList(TArray<TSubclassOf<UPhase>> PhasesArray);
	FAllPhasesCompleted OnAllPhasesCompleted;
};
