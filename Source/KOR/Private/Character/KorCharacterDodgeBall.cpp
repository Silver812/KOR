// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/KorCharacterDodgeBall.h"
#include "Character/AC_Grabbing.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AKorCharacterDodgeBall::AKorCharacterDodgeBall()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AKorCharacterDodgeBall::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AKorCharacterDodgeBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetOwner() == UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		if (GrabbingComponent->isGrabbing)
		{
			DetectPlayersInCone();
			Grabbed = true;
		}
		else
		{
			if (Grabbed)
			{
				Grabbed = false;
				SelectPositionToThrowItem();
			}
		}
	}
}

// Called to bind functionality to input
void AKorCharacterDodgeBall::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AKorCharacterDodgeBall::DetectPlayersInCone()
{
	InsideCone.Empty();
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AKorCharacterDodgeBall::GetClass(), FoundActors);
	for (AActor* Actor : FoundActors)
	{
		if (Actor != this)
		{
			FVector velocity = GetCharacterMovement()->Velocity;
			velocity.Normalize();
			FVector DirVector = Actor->GetActorLocation() - GetActorLocation();
			DirVector.Normalize();

			if (FVector::DotProduct(velocity, DirVector) >= 0.8f)
			{
				DrawDebugSphere(GetWorld(), Actor->GetActorLocation(), 100, 12, FColor::Emerald, true, 2);
				InsideCone.AddUnique(Actor);
			}
		}
	}
}

void AKorCharacterDodgeBall::SelectPositionToThrowItem()
{
	float Distance = 10000000.0f;
	SelectedPosition = FVector::Zero();

	for (auto Actor : InsideCone)
	{
		float newDistance = FVector::Distance(Actor->GetActorLocation(), GetActorLocation());
		if (newDistance < Distance)
		{
			Distance = newDistance;
			SelectedPosition = Actor->GetActorLocation();
		}
	}
	
	DrawDebugSphere(GetWorld(), SelectedPosition, 100, 12, FColor::Orange, true, 2);
}
