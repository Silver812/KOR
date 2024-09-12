// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/KORSpectator.h"

AKORSpectator::AKORSpectator()
{
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);
}

void AKORSpectator::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AKORSpectator::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AKORSpectator::MoveRight);
}

void AKORSpectator::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		if (PlayerController)
		{
			FRotator ControlRotation = PlayerController->GetControlRotation();
			FRotator YawRotation(0, ControlRotation.Yaw, 0);

			// Calculate forward direction
			FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}
	}
}

void AKORSpectator::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		APlayerController* PlayerController = Cast<APlayerController>(GetController());
		if (PlayerController)
		{
			FRotator ControlRotation = PlayerController->GetControlRotation();
			FRotator YawRotation(0, ControlRotation.Yaw, 0);

			// Calculate right direction
			FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			AddMovementInput(Direction, Value);
		}
	}
}