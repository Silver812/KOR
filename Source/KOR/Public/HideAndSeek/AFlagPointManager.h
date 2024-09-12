// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AFlagPointManager.generated.h"

UCLASS()
class KOR_API AAFlagPointManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAFlagPointManager();

	//--------------------FLAG MANAGER VARIABLES-----------------------------------------------------//
	UPROPERTY(EditAnywhere, Category = ObjectMesh, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> ClassToFind;

	UPROPERTY(EditAnywhere, Category = ObjectMesh, meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> FoundActors;

	UPROPERTY(EditAnywhere, Category = ObjectMesh, meta = (AllowPrivateAccess = "true"))
	AActor* arrayOfFlags[1];
	
	//-----------------------------FLAG MANAGER FUNCTIONS---------------------------------------------------//

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
