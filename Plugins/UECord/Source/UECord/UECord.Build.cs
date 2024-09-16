// Copyright (c) 2024 hezaerd.com

using UnrealBuildTool;

public class UECord : ModuleRules
{
	public UECord(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		bUseUnity = false;
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"DiscordGameSDK",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Projects"
				// ... add private dependencies that you statically link with here ...	
			}
			);
	}
}
