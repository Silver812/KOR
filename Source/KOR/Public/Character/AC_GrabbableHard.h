// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AC_GrabbableBase.h"
#include "AC_GrabbableHard.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KOR_API UAC_GrabbableHard : public UAC_GrabbableBase
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAC_GrabbableHard();

protected:

	UFUNCTION(Server, Reliable)
	virtual void Grab_Server(UStaticMeshComponent* Hand) override;
	
	UFUNCTION(Server, Reliable)
	virtual void EndGrab_Server(UStaticMeshComponent* Hand) override;

	UFUNCTION(BlueprintCallable,Server, Reliable)
	virtual void ApplyForce_Server(FVector Direction, float Force) override;
};
