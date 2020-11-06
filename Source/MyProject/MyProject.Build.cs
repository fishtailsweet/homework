// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MyProject : ModuleRules
{
	public MyProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG" });
		// �轫UMG��ӵ������Ĺ���ģ���б��У�����Slate��SlateCore��ӵ�������˽��ģ���б���
		// ����UMG�󣬿�����Ŀ���Զ���GameMode����Ӵ��룬�Դ�������ʾ��Ϸ�˵�
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		// ��ʹ��Slate UI����ȡ��ע��

		// PrivateDependencyModuleNames.Add("OnlineSubsystem");
		// if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64))
		// {
		//      if (UEBuildConfiguration.bCompileSteamOSS == true)
		//      {
		//          DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
		//      }
		// }
		// ��ʹ�����߹��ܣ���ȡ��ע��
	}
}
