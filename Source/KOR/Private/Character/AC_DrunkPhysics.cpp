// Fill out your copyright notice in the Description page of Project Settings.

#include "Character//AC_DrunkPhysics.h"

// Sets default values for this component's properties
UAC_DrunkPhysics::UAC_DrunkPhysics()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UAC_DrunkPhysics::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UAC_DrunkPhysics::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAC_DrunkPhysics::DrunkMesh(USkeletalMeshComponent* SkeletalMesh,
                                 UPhysicalAnimationComponent* PhysicalAnimationComponent, FName BoneName)
{
	BFL_DrunkMesh(SkeletalMesh, PhysicalAnimationComponent, BoneName, AnimationData);
	UE_LOG(LogTemp, Warning, TEXT("UAC_DrunkPhysics::DrunkMesh activated, %s"), *BoneName.ToString());
}

void UAC_DrunkPhysics::BFL_DrunkMesh(USkeletalMeshComponent* SkeletalMesh,
                                     UPhysicalAnimationComponent* PhysicalAnimationComponent, FName BoneName,
                                     FPhysicalAnimationData AnimationDataRef)
{
	UE_LOG(LogTemp, Warning, TEXT("UAC_DrunkPhysics::BFL_DrunkMesh activated"))
	PhysicalAnimationComponent->SetSkeletalMeshComponent(SkeletalMesh);

	if (SkeletalMesh)
	{
		bool bShouldSimulatePhysics = true; // SimulatePhysics = true
		bool bIncludeSelf = true; // Include the bone of BoneName to simulate physics
		SkeletalMesh->SetAllBodiesBelowSimulatePhysics(BoneName, bShouldSimulatePhysics, bIncludeSelf);
	}
}
