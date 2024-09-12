// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicalAnimationComponent.h"
#include "AC_DrunkPhysics.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KOR_API UAC_DrunkPhysics : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAC_DrunkPhysics();
	
	UPROPERTY(EditAnywhere, Category = "DrunkMeshAnimationData")
	FPhysicalAnimationData AnimationData;

	void DrunkMesh(USkeletalMeshComponent* SkeletalMesh, UPhysicalAnimationComponent* PhysicalAnimationComponent,
	               FName BoneName);

	void BFL_DrunkMesh(USkeletalMeshComponent* SkeletalMesh, UPhysicalAnimationComponent* PhysicalAnimationComponent,
	                   FName BoneName, FPhysicalAnimationData AnimationDataRef);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
