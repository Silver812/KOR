﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/KORGS.h"
#include "Net/UnrealNetwork.h"

void AKORGS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AKORGS, NewSpectatorClass);
}