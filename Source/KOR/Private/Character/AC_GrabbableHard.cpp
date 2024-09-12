// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/AC_GrabbableHard.h"
#include "ADestructibleObjects/ACDestructibleObjectComponent.h"
#include "ADestructibleObjects/ADestructibleObj.h"

UAC_GrabbableHard::UAC_GrabbableHard()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAC_GrabbableHard::Grab_Server_Implementation(UStaticMeshComponent* Hand)
{
	Super::Grab_Server(Hand);

	const FAttachmentTransformRules AttachmentRules(
		EAttachmentRule::SnapToTarget, // Location
		EAttachmentRule::KeepRelative, // Rotation
		EAttachmentRule::KeepWorld, // Scale
		true // Weld simulated bodies
	);

	GetOwner()->FindComponentByClass<UStaticMeshComponent>()->AttachToComponent(Hand, AttachmentRules);
}

void UAC_GrabbableHard::EndGrab_Server_Implementation(UStaticMeshComponent* Hand)
{
	Super::EndGrab_Server(Hand);
	const FDetachmentTransformRules DetachmentRules(
		EDetachmentRule::KeepWorld, // Location
		EDetachmentRule::KeepWorld, // Rotation
		EDetachmentRule::KeepWorld, // Scale
		true // Weld simulated bodies
	);

	if (GetOwner()->FindComponentByClass<UACDestructibleObjectComponent>())
	{
		if (GetOwner()->FindComponentByClass<UACDestructibleObjectComponent>()->DestroyProbability())
		{
			Cast<AADestructibleObj>(GetOwner())->characterRef = Cast<AKORCharacter>(Hand->GetOwner());

			GetOwner()->FindComponentByClass<UACDestructibleObjectComponent>()->hasBeenTrhown = true;
		}
	}

	GetOwner()->DetachFromActor(DetachmentRules);
	GetOwner()->FindComponentByClass<UStaticMeshComponent>()->SetSimulatePhysics(true);
}

void UAC_GrabbableHard::ApplyForce_Server_Implementation(FVector Direction, float Force)
{
	Super::ApplyForce_Server(Direction, Force);
}
