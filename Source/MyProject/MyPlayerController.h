// Fill out your copyright notice in the Description page of Project Settings.

// 需要在 玩家控制器（Player Controller） 类上设置输入模式
// 游戏开始时，只需在此类中调用一个额外函数，便能确保与UI元素进行交互
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
