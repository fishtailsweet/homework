// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();
    SetInputMode(FInputModeGameAndUI());
}
// �������ѹ�����ϣ��Դ�������ʾ�˵���������Ҫʱ����ɾ�������ڷ��� ��ñ༭������ʼ��Ʋ˵���Դ�ɣ����ô˲����ɽ� �û��ؼ� �����˵�