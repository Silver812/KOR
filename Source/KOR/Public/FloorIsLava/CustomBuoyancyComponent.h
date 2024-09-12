// BuoyancyComponent.h

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CustomBuoyancyComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KOR_API UCustomBuoyancyComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCustomBuoyancyComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	UPrimitiveComponent* PrimitiveComponent;

public:
	// Called every frame
	//virtual void AsyncPhysicsTickComponent(float DeltaTime, float SimTime) override;
	FVector GetBuoyancyForce(float Depth, float DeltaTime) const;

private:
	UPROPERTY(EditAnywhere)
	float BuoyancyForce = 1000.0f; // Adjust this value as needed for desired buoyancy
	
	UPROPERTY(EditAnywhere)
	float Gravity = 980.0f; // Gravity acceleration (cm/s^2)

	UPROPERTY(EditAnywhere)
	float MaxBuoyancyDepth = 500.0f; // Maximum depth for buoyancy calculation

	UPROPERTY(EditAnywhere)
	float MinBuoyancyDepth = 50.0f; // Minimum depth for buoyancy calculation

	UPROPERTY(EditAnywhere)
	bool bDebugDraw = false; // Enable to draw debug information

	UPROPERTY(EditAnywhere)
	float MaxDepth = 100.0f; // Maximum depth before buoyancy starts to decrease

	UPROPERTY(EditAnywhere)
	float BuoyancyDamping = 10.0f; // Damping factor for buoyancy effect
	
	UPROPERTY(EditAnywhere)
	float WaterDensity = 1000.0f; // Density of the water (kg/m^3)
};

