// Fill out your copyright notice in the Description page of Project Settings.

#include "Character//AC_Grabbing.h"
#include "CoreMinimal.h"
#include "Character//AC_GrabbableBase.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UAC_Grabbing::UAC_Grabbing() //: ObjectTypes2()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

void UAC_Grabbing::SetHands(UStaticMeshComponent* Hand_left, UStaticMeshComponent* Hand_right)
{
	this->Hand_l = Hand_left;
	this->Hand_r = Hand_right;
}


bool UAC_Grabbing::AttempGrab()
{
	if (!bCanGrab)
	{
		return false;
	}
	
	FHitResult HitResult;
	FLinearColor TraceColor = FLinearColor();
	FLinearColor TraceHitColor = FLinearColor();
	TArray<AActor*> IgnoreActors;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	IgnoreActors.Add(GetOwner());

	bool bHit = UKismetSystemLibrary::SphereTraceSingleForObjects(
		GetWorld(),
		Hand_r->GetComponentLocation(), // Where to create the radius of sphere
		Hand_r->GetComponentLocation(),
		SphereRadiusDetection, //sphere radius measures //Create a variable
		ObjectTypes,
		false,
		IgnoreActors,
		EDrawDebugTrace::None,
		HitResult,
		true,
		TraceColor,
		TraceHitColor,
		0.0f
	);

	if (bHit)
	{
		GrabbedComponent = HitResult.GetActor()->GetComponentByClass<UAC_GrabbableBase>();
		// SAVING GRAB HARD IN GRABBING COMPONENNT
		if (GrabbedComponent != nullptr && GrabbedComponent->bCanBeGrabbed)
		{
			ObjToApplyForce = GrabbedComponent;
			GrabbedComponent->Grab_Server(Hand_l);
		}
		else
		{
			GrabbedComponent = nullptr;
		}
	}
	return bHit;
}

void UAC_Grabbing::SetCanGrab()
{
	bCanGrab = true;
}

void UAC_Grabbing::EndGrab()
{
	if (GrabbedComponent != nullptr && bCanGrab)
	{
		bCanGrab = false;
		GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &UAC_Grabbing::SetCanGrab, GrabRate, false);
		GrabbedComponent->EndGrab_Server(Hand_l);
		GrabbedComponent->ApplyForce_Server(GetOwner()->GetActorForwardVector(), ThrowForce);
		Hand_l->AddImpulse(GetOwner()->GetActorForwardVector() * ThrowForce * .7, NAME_None, true);
		GrabbedComponent = nullptr;
	}
}

void UAC_Grabbing::IsGrabbingFalse_Implementation()
{
	isGrabbing = false;
}

void UAC_Grabbing::IsGrabbingTrue_Implementation()
{
	isGrabbing = true;
}
