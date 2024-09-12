// Fill out your copyright notice in the Description page of Project Settings.

#include "HideAndSeek/AFlagPointManager.h"

// Sets default values
AAFlagPointManager::AAFlagPointManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAFlagPointManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAFlagPointManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

