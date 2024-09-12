// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/KORCharacter.h"
#include "KorNPCBase.generated.h"

class UBlackboardData;
class UBehaviorTree;

UCLASS()
class KOR_API AKorNPCBase : public AKORCharacter
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "AIData", meta=(AllowPrivateAccess = true))
	UBehaviorTree* BehaviorTreeAsset;

	UPROPERTY(EditDefaultsOnly, Category = "AIData", meta=(AllowPrivateAccess = true))
	UBlackboardData* BlackboardData;

public:
	// Sets default values for this character's properties
	AKorNPCBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UBehaviorTree* GetBehaviorTreeAsset() const
	{
		return BehaviorTreeAsset;
	}

	UBlackboardData* GetBlackboardAsset() const
	{
		return BlackboardData;
	}
};
