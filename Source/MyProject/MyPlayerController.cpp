// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();
    SetInputMode(FInputModeGameAndUI());
}
// 代码框架已构建完毕，以创建和显示菜单并在无需要时将其删除。现在返回 虚幻编辑器，开始设计菜单资源吧！利用此操作可将 用户控件 用作菜单