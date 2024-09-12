// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "KorGI.generated.h"

class ATextRenderActor;class UKorGMDefinition;

USTRUCT(BlueprintType)
struct FSession
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Session")
	int MaxPlayers = 0;

	FSession(const int NewMaxPlayers = 0) : MaxPlayers(NewMaxPlayers) {}
};

UCLASS()
class KOR_API UKorGI : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Config")
	FSession Session;

	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<APawn> PlayerPawn;
	
	UPROPERTY(EditAnywhere, Category = "Config")
	int32 PlayerColorIndex = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
	FName PlayerName;

	// Only one data asset per level. For example, either DA_Lobby or DA_LobbyFinal
	UPROPERTY(EditAnywhere, Category = "Config")
	TMap<FName, TObjectPtr<UKorGMDefinition>> GMDefinitionsMap;

	// Backup to restore the original values after each math ends
	UPROPERTY(EditAnywhere, Category = "Config")
	TMap<FName, TObjectPtr<UKorGMDefinition>> GMDefinitionsListBackup;

	// Table where all the GMDefinitions are stored and selected from the editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GMDefinition")
	TObjectPtr<UDataTable> GMDefTable;

	UFUNCTION(BlueprintCallable, Category = "Session")
	void SetMaxPlayers(int NewMaxPlayers) { Session.MaxPlayers = NewMaxPlayers; }

	UFUNCTION(BlueprintCallable, Category="Config")
	UKorGMDefinition* GetGMDefinition(FName GMName) const { return GMDefinitionsMap[GMName]; }

	UFUNCTION(BlueprintCallable, Category="Config")
	void SetGMDefinition(FName GMName, UKorGMDefinition* GMDefinition) { GMDefinitionsMap.Add(GMName, GMDefinition); }
	
	// This method should only be called on the server since the KorScorer only exists on the server
	UFUNCTION(BlueprintCallable, Category="Config")
	void ResetGMDefinitionsList() { GMDefinitionsMap = GMDefinitionsListBackup; }

	// Debug
	UFUNCTION(BlueprintCallable, Category="Config")
	void PrintGMDefinitionsList() const;
};
