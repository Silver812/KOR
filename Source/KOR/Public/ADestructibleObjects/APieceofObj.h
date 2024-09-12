// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h" //Collider
#include "Components/SceneComponent.h" //Scene component !
#include "Character/AC_GrabbableHard.h"//AC_Grabbablehard Ref
#include "Engine/EngineTypes.h" //FREPMovment
#include "APieceofObj.generated.h"

class UStaticMeshComponent; //ObjectMeshComp
class UStaticMesh; //StaticMesVariable
class UBoxComponent; //Collider

UCLASS()
class KOR_API AAPieceofObj : public AActor
{
	GENERATED_BODY()

public:
	AAPieceofObj();

	//---------------------------------MESH VARIABLES---------------------------------------------------//

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PieceObjMeshComp, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* PieceObj_MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PieceObjMesh, meta = (AllowPrivateAccess = "true"))
	UStaticMesh* PieceObj_StaticMesh;

	UPROPERTY(VisibleAnywhere, Category = PieceObjCollider, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* PieceObj_BoxCollider;

	UPROPERTY(EditAnywhere, Category = GrabbaleComponet, meta = (AllowPrivateAccess = "true"))
	UAC_GrabbableHard* GrabbableHardComponent;
	
	//-----------------------------FUNCTIONS---------------------------------------------------------//
	
	void SetStaticMesh();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	
	
};
