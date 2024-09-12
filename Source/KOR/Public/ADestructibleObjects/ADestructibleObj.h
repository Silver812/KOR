// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ACDestructibleObjectComponent.h"//DestructibleObjtComp
#include "Character/AC_GrabbableHard.h"//AC_Grabbablehard Ref
#include "Components/BoxComponent.h" //Collider
#include "Components/SceneComponent.h" //Scene component for SpawnPoint !
#include "Character/KORCharacter.h" // KOR CHARACTER REF!
#include "ADestructibleObj.generated.h"

class UStaticMeshComponent; //ObjectMesh
class UBoxComponent; //Collider
class USceneComponent; //Scene Comp

UCLASS()
class KOR_API AADestructibleObj : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AADestructibleObj();

	//---------------------------------MESH VARIABLES---------------------------------------------------//

	UPROPERTY(EditAnywhere, Category = ObjectMesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Object_MeshComp;

	UPROPERTY(VisibleAnywhere, Category = SpawnPoint_SceneComponent, meta = (AllowPrivateAccess = "true"))
	USceneComponent* SpawnPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = DestructibleObjectComponent,
		meta = (AllowPrivateAccess = "true"))
	UACDestructibleObjectComponent* DestructibleObjectComp;

	bool bSpawned = false;

	UPROPERTY(VisibleAnywhere, Category = TeleporterVariables, meta = (AllowPrivateAccess = "true"))
	AKORCharacter* characterRef;

	UPROPERTY(EditAnywhere, Category = TeleporterVariables, meta = (AllowPrivateAccess = "true"))
	UAC_GrabbableHard* GrabbableHardComponent;

	UPROPERTY(EditAnywhere, Category = TeleporterVariables, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* boxCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraComponent* ObjNiagaraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool destroyWithOnlyOneTouch = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool soundPlayed = false;

	//-----------------------------FUNCTIONS---------------------------------------------------------//

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                       int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,
	           FVector NormalImpulse, const FHitResult& Hit);

	float localResistance = 0.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
