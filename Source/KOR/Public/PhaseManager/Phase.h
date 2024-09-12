// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Phase.generated.h"

DECLARE_MULTICAST_DELEGATE(FPhaseCompleted)

UCLASS(Blueprintable, meta = (ShowWorldContextPin))
class KOR_API UPhase : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Phase")
	void OnPhaseActivated();

	FPhaseCompleted PhaseCompleted;

	UPROPERTY(BlueprintReadOnly)
	UWorld* WorldContext;

protected:
	UFUNCTION(BlueprintCallable, Category = "Phase")
	void PhaseEnd();
};
