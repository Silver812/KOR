// Fill out your copyright notice in the Description page of Project Settings.

#include "Minigames/PointBasedMaxWinner.h"

void UPointBasedMaxWinner::Score(TMap<FName, int32>& PlayerScores)
{
	Super::Score(PlayerScores);

	// Sort the players by score in descending order
	PlayerScores.ValueSort([](int32 A, int32 B) { return A > B; });
	
	for (auto& Player : PlayerScores)
	{
		Player.Value = static_cast<int>(ceil(MaxScore - ((MaxScore / PlayerScores.Num()) * Count)));

		if (Player.Value != 0)
		{
			Count += CountAdvancer;
		}
	}
}
