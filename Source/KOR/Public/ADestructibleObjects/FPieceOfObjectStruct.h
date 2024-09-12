// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPieceOfObjectStruct.generated.h"

USTRUCT(BlueprintType)
struct KOR_API FPieceOfObjectStruct
{
	GENERATED_BODY()
	
	FPieceOfObjectStruct();
	~FPieceOfObjectStruct();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* PieceObjectStaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int numberOfPieces = 0;
};
