// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using UnrealBuildTool.Rules;

public class FrontEndUI : ModuleRules
{
	public FrontEndUI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore", 
			"EnhancedInput",
            "GameplayTags",//Gameplay标签模块
			"UMG",//用户界面模块
			"CommonInput"//CommonUI插件中的输入系统,为解决多平台的输入设备切换和UI交互
        });

        // 仅在编辑器构建中添加对UnrealEd的依赖
        if (Target.bBuildEditor)
        {
            PrivateDependencyModuleNames.AddRange(
                new string[] {
                    "UnrealEd"
                }
            );
        }
        PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
