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
                "Core",
                "HTTP"
            }
            );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Json",
                "JsonUtilities"
            }
            );

        if (Target.Type == TargetType.Editor)
        {
            PrivateDependencyModuleNames.AddRange(
                new string[]
                {
                    "Settings"
                }
            );
        }
    }
}
