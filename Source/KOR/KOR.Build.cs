// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class KOR : ModuleRules
{
	public KOR(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" ,"UMG", "ModularGameplay", "AIModule", "NetCore", "Niagara" });
		PublicIncludePaths.Add("KOR/Public");
	}
}
