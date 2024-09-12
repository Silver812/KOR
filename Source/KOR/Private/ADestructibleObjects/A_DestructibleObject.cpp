// Fill out your copyright notice in the Description page of Project Settings.

#include "ADestructibleObjects/A_DestructibleObject.h"

// Sets default values
AA_DestructibleObject::AA_DestructibleObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AA_DestructibleObject::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AA_DestructibleObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
