// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyProject : ModuleRules
{
	public MyProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG" });
		// 需将UMG添加到包含的公共模块列表中，并将Slate和SlateCore添加到包含的私有模块列表中
		// 设置UMG后，可在项目的自定义GameMode中添加代码，以创建和显示游戏菜单
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		// 如使用Slate UI，则取消注释

		// PrivateDependencyModuleNames.Add("OnlineSubsystem");
		// if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64))
		// {
		//      if (UEBuildConfiguration.bCompileSteamOSS == true)
		//      {
		//          DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
		//      }
		// }
		// 如使用在线功能，则取消注释
	}
}
