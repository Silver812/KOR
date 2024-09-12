// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/KORBaseHUD.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AKORBaseHUD::PushWidget(const TSubclassOf<UUserWidget> InWidgetClass, EInputMode inputMode)
{
	if (!InWidgetClass)
	{
		return;
	}
	
	if (WidgetStack.IsValidIndex(0))
	{
		if (UUserWidget* prevWidget = WidgetStack[0].Widget)
		{
			prevWidget->RemoveFromParent(); //Disable previous menu
		}
	}
	
	FUIandInputMode NewEntry;
	NewEntry.Widget = CreateWidget(GetOwningPlayerController(), InWidgetClass);
	NewEntry.InputMode = inputMode;
	WidgetStack.Push(NewEntry);
	NewEntry.Widget->AddToViewport();
	SetInputMode(inputMode);
}


void AKORBaseHUD::PopWidget()
{
	if (WidgetStack.IsValidIndex(0))
	{
		if (UUserWidget* prevWidget = WidgetStack.Pop().Widget)
		{
			prevWidget->RemoveFromParent();
		}
	}
	if (WidgetStack.IsValidIndex(0))
	{
		if (UUserWidget* currWidget = WidgetStack.Last().Widget)
		{
			// TODO: fix crash here after click on Continue on PauseMenu
			currWidget->AddToViewport();
		}
	}
}

void AKORBaseHUD::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0))
	{
		if (AKORBaseHUD* HUD = Cast<AKORBaseHUD>(PC->GetHUD()))
		{
			HUD->PushWidget(UIClass, InputModeNew);
		}
	}
}

void AKORBaseHUD::SetInputMode(const EInputMode InInputMode)
{
	switch (InInputMode)
	{
	case EInputMode::Game:
		{
			FInputModeGameOnly InputModeGame;
			InputModeGame.SetConsumeCaptureMouseDown(true);
			if (GetOwningPlayerController())
			{
				GetOwningPlayerController()->SetInputMode(InputModeGame);
				GetOwningPlayerController()->SetShowMouseCursor(false);
			}
		}
		break;
	case EInputMode::UI:
		{
			FInputModeUIOnly InputModeUI;
			InputModeUI.SetWidgetToFocus(WidgetStack.Last().Widget->TakeWidget());
			if (GetOwningPlayerController())
			{
				GetOwningPlayerController()->SetInputMode(InputModeUI);
				GetOwningPlayerController()->SetShowMouseCursor(true);
			}
		}
		break;
	case EInputMode::GameAndUI:
		{
			FInputModeGameAndUI InputModeGameUI;
			InputModeGameUI.SetWidgetToFocus(WidgetStack.Last().Widget->TakeWidget());
			InputModeGameUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			if (GetOwningPlayerController())
			{
				GetOwningPlayerController()->SetInputMode(InputModeGameUI);
				GetOwningPlayerController()->SetShowMouseCursor(true);
			}
		}
		break;
	}
}


void AKORBaseHUD::ShowPauseMenu()
{
	if (bShowingPauseMenu)
	{
		PopWidget();
		bShowingPauseMenu = false;
		return;
	}

	PushWidget(PauseClass, EInputMode::GameAndUI);
	bShowingPauseMenu = true;
}
