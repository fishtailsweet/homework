// Fill out your copyright notice in the Description page of Project Settings.

// ��Ҫ�� ��ҿ�������Player Controller�� ������������ģʽ
// ��Ϸ��ʼʱ��ֻ���ڴ����е���һ�����⺯��������ȷ����UIԪ�ؽ��н���
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
};
