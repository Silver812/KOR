// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/KorBaseGM.h"
#include "MiniGM.generated.h"

class UKorGMDefinition;

UCLASS()
class KOR_API AMiniGM : public AKorBaseGM
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName MusicTag = TEXT("music");

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName SectionNameTag = TEXT("Ending");
	
protected:
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

	UFUNCTION()
	void EndMinigame(const TMap<FName, int32>& PlayerScores) const;
	
public:
	virtual void BeginPlay() override;
};
