// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KorBaseGM.generated.h"

class UPhaseManager;
class UKorGMDefinition;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAddPlayersCompleted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerJoined_DelegateHandle, APlayerController*, PlayerController);

UCLASS()
class KOR_API AKorBaseGM : public AGameModeBase
{
	GENERATED_BODY()
	
	UPROPERTY()
	TArray<APlayerController*> PlayerControllers;

	virtual void PreInitializeComponents() override;
	
protected:
	
	UPROPERTY(BlueprintReadWrite, BlueprintAssignable)
	FOnAddPlayersCompleted OnAddPlayersCompleted;

	UPROPERTY(BlueprintReadWrite, BlueprintAssignable)
	FOnPlayerJoined_DelegateHandle OnPlayerJoined;

	virtual void AllPlayersAdded();
	void CreatePawnForPlayerController(APlayerController* PC);

	UFUNCTION(BlueprintCallable)
	void ChangeToNewSceneServerListen(const TSoftObjectPtr<UWorld>& Level);

	UFUNCTION(BlueprintCallable)
	void ChangeToNewSceneServerListenPath(const FString& LevelPath);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Phase Manager")
	UPhaseManager* PhaseManager;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GMDefinition")
	TObjectPtr<UKorGMDefinition> GMDefinition;

	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;
	
	virtual void InitGameState() override;
	
public:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool bAllPlayersAdded = false;
	
	AKorBaseGM();
	virtual void BeginPlay() override;
	UKorGMDefinition* GetGMDefinition() const;

	UFUNCTION(BlueprintCallable)
	TArray<APlayerController*> GetPlayerControllers() const;

	// Array with the materials for the player colors
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "GMDefinition")
	TArray<UMaterialInterface*> PlayerColors;
};
