// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "APieceofObj.h"
#include "Components/ActorComponent.h"
#include "UObject/Class.h" //enums
#include "EDestructibleObjType.h" //Enumeration!
#include "FDestructibleObjectStruct.h"
#include "GameFramework/Actor.h" // ACTOR
#include "ACDestructibleObjectComponent.generated.h"

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KOR_API UACDestructibleObjectComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	//------------------------Component VARIABLES---------------------------------------------//
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Struct, meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EDestructibleObjType> objType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Struct, meta = (AllowPrivateAccess = "true"))
	FDestructibleObjectStruct ObjStruct;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Struct, meta = (AllowPrivateAccess = "true"))
	bool hasBeenTrhown = false;
	
	UPROPERTY()
	AAPieceofObj* pieceOfObjRef;
	
	//------------------------Component FUNCTIONS---------------------------------------------//
	
	bool DestroyProbability();

	UFUNCTION(Server,Reliable)//Replicated on server 
	void SpawnOnePiece(FTransform spawnPointTrans, int i);

	UFUNCTION(Server,Reliable)//Replicated on server
	void SpawnPieces(FTransform spawnPointTrans);

	UFUNCTION(Server,Reliable)//Replicated on server
	void DestroyDestructibleObj(FTransform spawnPointTrans);

	UFUNCTION(NetMulticast, Reliable)
	void DestructibleEffect(FTransform spawnPointTrans);

	UFUNCTION(Server, Reliable)
	void MakingNoise(FTransform spawnPointTrans,AActor* OverlapedActor);

	UFUNCTION(Server, Reliable)
	void CountdownToMakeNoise();

	FTimerHandle TimerHandleNoise;
	float waitingToMakeNoise = 0.0f;
	
	// Sets default values for this component's properties
	UACDestructibleObjectComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
