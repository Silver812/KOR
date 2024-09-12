// Fill out your copyright notice in the Description page of Project Settings.

#include "PhaseManager/Phase.h"

void UPhase::OnPhaseActivated_Implementation()
{
}

void UPhase::PhaseEnd()
{
	PhaseCompleted.Broadcast();
}
