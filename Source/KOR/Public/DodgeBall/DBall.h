// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DBall.generated.h"

class AKorCharacterDodgeBall;
class UAC_GrabbableHard;

UCLASS()
class KOR_API ADBall : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADBall();
	
	UPROPERTY(EditAnywhere, Category = Config, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = TeleporterVariables, meta = (AllowPrivateAccess = "true"))
	AKorCharacterDodgeBall* characterRef;

	UPROPERTY(EditAnywhere, Category = Config, meta = (AllowPrivateAccess = "true"))
	UAC_GrabbableHard* GrabbableHardComponent;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Grabbed();
	void EndGrabbed();
};
