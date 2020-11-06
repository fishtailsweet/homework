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
	// ���Ǹ��ࣨ�ɵ���Super���ã��еĺ���ʱ���������ڸ���StartPlay����ص��øú����ĸ���汾
	// ���ں����汾����ͼ�����й��̵�������Ӳ��裬����ڸú��������е��� Super::BeginPlay
	ChangeMenuWidget(StartingWidgetClass);
	//if (GEngine)
	//{
		// ��ʾ������Ϣ���롣 
		// -1"��"ֵ���׸�������˵������������»�ˢ�´���Ϣ��
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameMode!"));
	//}
}

// �趨��˵���ı仯�����ӿ��д��ڻ�Ծ���û��ؼ����轫���Ƴ���Ȼ����½��û��ؼ�����������ӵ��ӿ���
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
// �˴��뽫�������ṩ �ؼ� ��ʵ�����������������Ļ�ϡ��ô���ͬ���ɽ����Ƴ����Ա�ÿ�ν���һ����Ծ�ؼ������� ������� ��ͬʱ������ʾ����ؼ�����֮����
// �������Ӵ��н����Ƴ������(���޸�)����������б�����������������������������ϵͳ����������������ֱ�����ٿؼ�