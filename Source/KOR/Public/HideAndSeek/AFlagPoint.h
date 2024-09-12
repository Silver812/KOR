// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Character/KORCharacter.h" // KOR CHARACTER REF!
#include "Components/SphereComponent.h" //Collider
#include "AFlagPoint.generated.h"

class UStaticMeshComponent; //ObjectMesh
class UStaticMesh;
class USphereComponentComponent; //Collider

UCLASS()
class KOR_API AAFlagPoint : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAFlagPoint();


	//--------------------FLAG POINT COMPONENTS--------------------------------------------------//

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ObjectMesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* FlagPointMeshComp;

	UPROPERTY(EditAnywhere, Category = ObjectMesh, meta = (AllowPrivateAccess = "true"))
	USphereComponent* sphereColliderComp;

	UPROPERTY(VisibleAnywhere, Category = TeleporterVariables, meta = (AllowPrivateAccess = "true"))
	AKORCharacter* characterRef;

	//-----------------------FLAG POINT VARIABLES-------------------------------------------------/

	UPROPERTY(EditAnywhere, Category = CandyFlagVariables, meta = (AllowPrivateAccess = "true"))
	bool activeFlagPoint = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CandyFlagVariables, meta = (AllowPrivateAccess = "true"))
	bool bSleeping = true;

	UPROPERTY(EditAnywhere, Category = DelaySleepingTime, meta = (AllowPrivateAccess = "true"))
	float delaySleepingTime = 5.0f;

	UPROPERTY(EditAnywhere, Category = Punctuation, meta = (AllowPrivateAccess = "true"))
	int punctuation = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VFX, meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* appearVFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = VFX, meta = (AllowPrivateAccess = "true"))
	UNiagaraSystem* DisappearVFX;

	float currentSleepingTime = 0.0f;
	FTimerHandle flagPointTimer;
	
	//-----------------------FLAG POINT FUNCTIONS------------------------------------------------------//

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                       int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(Server, Reliable) //Replicated on server
	void FlagCatched();
	
	UFUNCTION(Server, Reliable) //Replicated on server
	void SetFlagStaticMesh(bool active);

	UFUNCTION(Server, Reliable) //Replicated on server
	void SetRandomSleepingDelay();

	UFUNCTION(Server, Reliable) //Replicated on server
	void SleepingTime();

	UFUNCTION(Server, Reliable) //Replicated on server
	void Countdown();

	UFUNCTION(Server, Reliable) //Replicated on server
	void ActiveFlagPoint();

	UFUNCTION(Server, Reliable) //Replicated on server
	void ActiveVFX();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
