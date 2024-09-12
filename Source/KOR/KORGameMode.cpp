// Copyright Epic Games, Inc. All Rights Reserved.

#include "KORGameMode.h"
#include "Character/KORCharacter.h"
#include "UObject/ConstructorHelpers.h"

AKORGameMode::AKORGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
