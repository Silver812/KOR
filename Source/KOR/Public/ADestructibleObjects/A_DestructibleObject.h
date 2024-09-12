﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A_DestructibleObject.generated.h"

UCLASS()
class KOR_API AA_DestructibleObject : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AA_DestructibleObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
