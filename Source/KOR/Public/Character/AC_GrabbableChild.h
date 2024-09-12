// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AC_GrabbableBase.h"
#include "Components/CapsuleComponent.h"
#include "AC_GrabbableChild.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KOR_API UAC_GrabbableChild : public UAC_GrabbableBase
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UAC_GrabbableChild();

protected:

	UFUNCTION(NetMulticast, Reliable)
	virtual void Grab_Server(UStaticMeshComponent* Hand) override;

	UFUNCTION(NetMulticast, Reliable) // must have reliable to give importance on the call of the function
	virtual void Grab_Multicast(UStaticMeshComponent* Hand) override;

	UFUNCTION(NetMulticast, Reliable)
	virtual void EndGrab_Server(UStaticMeshComponent* Hand) override;

	UFUNCTION(NetMulticast, Reliable)
	virtual void EndGrab_Multicast(UStaticMeshComponent* Hand) override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(BlueprintReadWrite)
	bool bGrabChild;

	UPROPERTY(ReplicatedUsing=OnRep_Capsule_Updated, EditAnywhere, BlueprintReadWrite, Category = "CapsuleComponent")
	UCapsuleComponent* CapsuleComponent;

	UFUNCTION()
	void OnRep_Capsule_Updated();
};
