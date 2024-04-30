// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UPortfolio_RPG : ModuleRules
{
	public UPortfolio_RPG(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { 
            "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput"
            ,"AIModule" , "Niagara","NavigationSystem", "GameplayTasks"
        });

        //모듈 추가시 다른곳에 메모해 주세요.
        //병합할때 참고하겠습니다.

		PrivateDependencyModuleNames.AddRange(new string[] {  });
        PublicIncludePaths.Add("UPortfolio_RPG");
        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
