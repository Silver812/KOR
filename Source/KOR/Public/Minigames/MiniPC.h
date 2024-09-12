// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/KorBasePC.h"
#include "MiniPC.generated.h"

class UInputMappingContext;

UCLASS()
class KOR_API AMiniPC : public AKorBasePC
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
};
