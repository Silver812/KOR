// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "KorBasePS.generated.h"

class UKorGI;
/**
 * 
 */
UCLASS()
class KOR_API AKorBasePS : public APlayerState
{
	// Replicated Name of the player
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	FName PlayerName;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"), ReplicatedUsing = OnRep_PlayerColorIndex)
	int32 PlayerColorIndex;

	UPROPERTY(VisibleAnywhere, Category="Getter")
	UKorGI* KorGI;
	
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OnRep_PlayerColorIndex();

	UFUNCTION(BlueprintCallable)
	FName GetPlayerNameKor() const { return PlayerName; }
	
	UFUNCTION(Server, Reliable)
	void SetPlayerName_Server(FName NewPlayerName);

	UFUNCTION(Server, Reliable)
	void SetPlayerColor_Server(int32 NewPlayerColorIndex);

	UFUNCTION(BlueprintPure, Category="Getter")
	UKorGI* GetKorGI();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
