// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"	// Ϊ�ڴ�����ʹ���û��ؼ�
#include "MyProjectGameMode.generated.h"

UCLASS(minimalapi)
class AMyProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyProjectGameMode();
	virtual void StartPlay() override;
	/** �Ƴ���ǰ�˵��ؼ�������ָ���ࣨ���У����½��ؼ���*/
	UFUNCTION(BlueprintCallable, Category = "UMG Game")
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);
protected:
	/** ��Ϸ��ʼʱ�������˵��Ŀؼ��ࡣ*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
	TSubclassOf<UUserWidget> StartingWidgetClass;

	/** �����˵��Ŀؼ�ʵ����*/
	UPROPERTY()
	UUserWidget* CurrentWidget;
};
// �����Ĳ˵����� �û��ؼ� ��ɡ����д�������½�����ʾ�û��ؼ���Ȼ������Ϸ��ʼʱ���øú�����ͬʱ����׷�ٴ������ݣ��Ա�֮�����ɾ��
// ����Ŀ�����Զ���GameMode�࣬��ֱ�Ӵ�


