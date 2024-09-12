// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "PlatformSpawner.generated.h"

struct FFILPlatformStruct;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KOR_API UPlatformSpawner : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlatformSpawner();

protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION(BlueprintCallable, Category = "Data Driven")
	FFILPlatformStruct& GetPlatform(int Difficulty) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Driven")
	UDataTable* FILPlatformDT;
};
