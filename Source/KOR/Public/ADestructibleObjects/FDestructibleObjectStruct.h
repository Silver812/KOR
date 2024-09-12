// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EDestructibleObjType.h"
#include "FPieceOfObjectStruct.h"
#include "NiagaraSystem.h" //Niagara System .h
#include "FDestructibleObjectStruct.generated.h"

USTRUCT(BlueprintType, Blueprintable)
struct KOR_API FDestructibleObjectStruct : public FTableRowBase
{
	GENERATED_BODY()

	FDestructibleObjectStruct();
	virtual ~FDestructibleObjectStruct() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EDestructibleObjType> objType = None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = 0.0, UIMax = 10000.0))
	float objectMass= 100.0f;;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(UIMin = 0.0, UIMax = 100.0))
	float destroyProbability = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bJustOneObject = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraSystem* explosionVFX;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FPieceOfObjectStruct> staticMeshST;

	// Destruction sound
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* destructionSound;
};
