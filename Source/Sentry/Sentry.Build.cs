// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Sentry : ModuleRules
{
    public Sentry(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core"
            }
            );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "HTTP",
                "Json",
                "JsonUtilities"
            }
            );
    }
}
