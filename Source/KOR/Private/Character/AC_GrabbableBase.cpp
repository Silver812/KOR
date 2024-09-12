// Fill out your copyright notice in the Description page of Project Settings.

#include "Character//AC_GrabbableBase.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values for this component's properties
UAC_GrabbableBase::UAC_GrabbableBase()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

// Called when the game starts
void UAC_GrabbableBase::BeginPlay()
{
	Super::BeginPlay();
}

void UAC_GrabbableBase::Grab_Server(UStaticMeshComponent* Hand)
{
	if (Hand->GetOwner()->GetComponentByClass<UCharacterMovementComponent>())
	{
		Hand->GetOwner()->GetComponentByClass<UCharacterMovementComponent>()->MaxWalkSpeed = Hand->GetOwner()->
			GetComponentByClass<UCharacterMovementComponent>()->GetMaxSpeed() * SpeedModifier;
	}
}

void UAC_GrabbableBase::EndGrab_Server(UStaticMeshComponent* Hand)
{
	if (Hand->GetOwner()->GetComponentByClass<
		UCharacterMovementComponent>())
	{
		Hand->GetOwner()->GetComponentByClass<UCharacterMovementComponent>()->MaxWalkSpeed = Hand->GetOwner()->
			GetComponentByClass<UCharacterMovementComponent>()->GetMaxSpeed() / SpeedModifier;
	}
}

void UAC_GrabbableBase::ApplyForce_Server(FVector Direction, float Force)
{
	GetOwner()->GetComponentByClass<UStaticMeshComponent>()->AddImpulse(Direction * Force, NAME_None, true);
}
