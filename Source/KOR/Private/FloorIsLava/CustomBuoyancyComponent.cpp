// BuoyancyComponent.cpp

#include "FloorIsLava/CustomBuoyancyComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UCustomBuoyancyComponent::UCustomBuoyancyComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UCustomBuoyancyComponent::BeginPlay()
{
	Super::BeginPlay();
	PrimitiveComponent = GetOwner()->FindComponentByClass<UPrimitiveComponent>();
	
}

FVector UCustomBuoyancyComponent::GetBuoyancyForce(const float Depth, const float DeltaTime) const
{
	if (Depth > MaxDepth)
		return FVector::ZeroVector;

	const float BuoyancyDepth = FMath::Clamp(Depth, MaxBuoyancyDepth, MinBuoyancyDepth  );
	const float BuoyantForceMagnitude = BuoyancyForce* (((MaxDepth+ BuoyancyDepth) / (MaxDepth+MaxBuoyancyDepth)));

	// Apply damping based on BuoyancyDamping
	const float DampingForceMagnitude = BuoyancyDamping * BuoyantForceMagnitude;
	const FVector DampingForce = -GetOwner()->GetVelocity() * DampingForceMagnitude;
	// Archimedes' principle
	const FVector BuoyantForce = FVector(0.0f, 0.0f, BuoyantForceMagnitude) * DampingForce;
	return BuoyantForce * FVector(0.0f, 0.0f, Gravity * DeltaTime);
}

