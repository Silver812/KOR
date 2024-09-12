// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GoalComponent.generated.h"

class UKorScorer;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KOR_API UGoalComponent : public UBoxComponent
{
	GENERATED_BODY()

	UPROPERTY()
	UKorScorer* Scorer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TMap<FName, int> FinishedPlayers;

public:
	// Sets default values for this component's properties
	UGoalComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
