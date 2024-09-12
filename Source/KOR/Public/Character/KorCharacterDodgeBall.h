// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KORCharacter.h"
#include "KorCharacterDodgeBall.generated.h"

DECLARE_DELEGATE_OneParam(FOnBallGrabbed, FVector);

UCLASS()
class KOR_API AKorCharacterDodgeBall : public AKORCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AKorCharacterDodgeBall();
	FOnBallGrabbed OnBallGrabbed;
	
	UPROPERTY(VisibleAnywhere)
	bool Grabbed;
	
	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> InsideCone;
	
	UPROPERTY(VisibleAnywhere)
	FVector SelectedPosition;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void DetectPlayersInCone();
	void SelectPositionToThrowItem();
};
