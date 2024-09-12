// Fill out your copyright notice in the Description page of Project Settings.

#include "Minigames/LastInWinner.h"

void ULastInWinner::Score(TMap<FName, int32>& PlayerScores)
{
	Super::Score(PlayerScores);

	Count = PlayerScores.Num() - 1;

	for (auto& Player : PlayerScores)
	{
		Player.Value = static_cast<int>(ceil(MaxScore - ((MaxScore / PlayerScores.Num()) * Count)));

		if (Player.Value != 0)
		{
			Count += CountAdvancer;
		}
	}
}
