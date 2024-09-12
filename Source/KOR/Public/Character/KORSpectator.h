// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpectatorPawn.h"
#include "KORSpectator.generated.h"

UCLASS()
class KOR_API AKORSpectator : public ASpectatorPawn
{
	GENERATED_BODY()

public:
	AKORSpectator();
	virtual void MoveForward(float Value) override;
	virtual void MoveRight(float Value) override;

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
