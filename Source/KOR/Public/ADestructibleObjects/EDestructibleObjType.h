// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EDestructibleObjType.generated.h"

UENUM(BlueprintType)
enum EDestructibleObjType
{
	None = 0,
	Debug = 1,
	Chair = 2,
	Table = 3,
	PCtable = 4,
	PC = 5,
	Keyboard = 6,
	Trashcan = 7,
	Bookbox = 8,
	Ballcase = 9,
	Ladder = 10
};	
