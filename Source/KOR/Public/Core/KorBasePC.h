// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KorBasePC.generated.h"

class AKORCharacter;
class UInputMappingContext;
class APawn;

UCLASS()
class KOR_API AKorBasePC : public APlayerController
{
	GENERATED_BODY()
	
	// Array with the materials for the player colors
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Config", meta = (AllowPrivateAccess = "true"))
	TArray<UMaterialInterface*> PlayerColors;

	UPROPERTY()
	int32 CharacterBodyMaterialIndex = 2;
	
protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:
	AKorBasePC();
	
	UFUNCTION(BlueprintCallable)
	void SetPlayerColorMaterial(int32 NewPlayerColorIndex);
	
	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<APawn> PlayerPawn;

	UPROPERTY(EditAnywhere, Category = "Config")
	UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere, Category = "Config")
	AKORCharacter* PlayerCharacter;
	
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable, Category ="Gameplay", meta = (AllowPrivateAccess = true))
	void Die();

	UFUNCTION()
	AKORCharacter* GetPlayerCharacterRef();
	
protected:
	UFUNCTION(Server, Reliable)
	void ServerSwitchToSpectator();
	void ServerSwitchToSpectator_Implementation();
};
