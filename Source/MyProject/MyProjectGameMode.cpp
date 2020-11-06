// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProjectGameMode.h"
#include "MyProjectCharacter.h"
#include "MyHUD.h"
#include "UObject/ConstructorHelpers.h"

AMyProjectGameMode::AMyProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	static ConstructorHelpers::FClassFinder<AHUD> HUDBPClass(TEXT("/Game/BF_MyHUD"));
	if (HUDBPClass.Class != NULL)
	{
		HUDClass = HUDBPClass.Class;
	}
}
void AMyProjectGameMode::StartPlay() {
	Super::StartPlay();
	// 覆盖父类（由单词Super引用）中的函数时，正如现在覆盖StartPlay，务必调用该函数的父类版本
	// 由于函数版本仅意图在现有过程的最后增加步骤，因此在该函数首行中调用 Super::BeginPlay
	ChangeMenuWidget(StartingWidgetClass);
	//if (GEngine)
	//{
		// 显示调试信息五秒。 
		// -1"键"值（首个参数）说明我们无需更新或刷新此消息。
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameMode!"));
	//}
}

// 需定义菜单间的变化。如视口中存在活跃的用户控件，需将其移除。然后可新建用户控件，并将其添加到视口中
void AMyProjectGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}
// 此代码将创建所提供 控件 的实例，并将其放置在屏幕上。该代码同样可将其移除，以便每次仅有一个活跃控件，尽管 虚幻引擎 可同时处理显示多个控件并与之交互
// 由于在视窗中将其移除和清除(或修改)引用其的所有变量，都将导致虚幻引擎的垃圾回收系统将其清除，因此无需直接销毁控件