// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_Grabbing.generated.h"

class UAC_GrabbableBase;
class UPhysicsSpringComponent;
class UPhysicsConstraintComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KOR_API UAC_Grabbing : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Hand_l;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Hand_r;
	
	UPROPERTY(EditAnywhere, Category= "Components")
	float SphereRadiusDetection = 50;
	
	UPROPERTY(EditAnywhere, Category= "Components")
	float ThrowForce = 75000;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UAC_GrabbableBase* GrabbedComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly ,Category = "Components")
	bool isGrabbing;

	UPROPERTY()
	bool bCanGrab = true; 
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly , Category = "Components")
	UAC_GrabbableBase* ObjToApplyForce;
	
	UPROPERTY(EditAnywhere)
	float GrabRate = 1;
	
	FTimerHandle CooldownTimerHandle;

	// Sets default values for this component's properties
	UAC_Grabbing();

	void SetHands(UStaticMeshComponent* Hand_left, UStaticMeshComponent* Hand_right);
	bool AttempGrab();
	inline void SetCanGrab();
	void EndGrab();
	
	UFUNCTION(Server, Reliable)
	void IsGrabbingFalse();

	UPROPERTY(EditAnywhere, Category="Spring")
	UPhysicsConstraintComponent* PhysicalConstraintSoft; 

	UFUNCTION(Server, Reliable)
	void IsGrabbingTrue();
};
