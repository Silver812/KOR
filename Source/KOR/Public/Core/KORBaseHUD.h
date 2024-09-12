// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "KORBaseHUD.generated.h"

class UUserWidget;

UENUM(BlueprintType)
enum class EInputMode : uint8
{
	UI = 0,
	Game = 1,
	GameAndUI = 2
};

USTRUCT()
struct FUIandInputMode
{
	GENERATED_BODY()

	UPROPERTY()
	UUserWidget* Widget;

	UPROPERTY()
	EInputMode InputMode = EInputMode::UI;
};

UCLASS()
class KOR_API AKORBaseHUD : public AHUD
{
	GENERATED_BODY()
	TArray<FUIandInputMode> WidgetStack;

	//Widget class
	UPROPERTY(EditDefaultsOnly, Category ="Interface", meta= (AllowPrivateAccess = true))
	TSubclassOf<UUserWidget> PauseClass;

	bool bShowingPauseMenu = false;

public:
	//Datatable
	UPROPERTY(EditDefaultsOnly, Category ="Interface", meta= (AllowPrivateAccess = true))
	TSubclassOf<UUserWidget> UIClass;

	UPROPERTY(EditDefaultsOnly, Category ="Interface", meta= (AllowPrivateAccess = true))
	EInputMode InputModeNew;

	UFUNCTION(BlueprintCallable)
	virtual void PushWidget(const TSubclassOf<UUserWidget> InWidgetClass, EInputMode inputMode);

	UFUNCTION(BlueprintCallable)
	virtual void PopWidget();

	UFUNCTION(BlueprintCallable, Category = "KOR|HUD")
	void ShowPauseMenu();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION(BlueprintCallable, Category = "KOR|HUD")
	void SetInputMode(const EInputMode InInputMode);
};
