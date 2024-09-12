// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_GrabbableBase.generated.h"

UCLASS(Abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KOR_API UAC_GrabbableBase : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAC_GrabbableBase();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	float SpeedModifier = .8;

public:
	UPROPERTY(EditAnywhere)
	bool bCanBeGrabbed = true;

	virtual void Grab(UStaticMeshComponent* Hand){}
	virtual void Grab_Server(UStaticMeshComponent* Hand);
	virtual void Grab_Multicast(UStaticMeshComponent* Hand){}
	
	virtual void EndGrab(UStaticMeshComponent* Hand){}
	virtual void EndGrab_Server(UStaticMeshComponent* Hand);
	virtual void EndGrab_Multicast(UStaticMeshComponent* Hand){}

	virtual void ApplyForce_Server(FVector Direction, float Force);
};
