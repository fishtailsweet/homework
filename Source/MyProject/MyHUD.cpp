// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Runtime/Engine/Classes/Engine/Canvas.h"
void AMyHUD::DrawHUD()
{
    Super::DrawHUD();

    if (CrosshairTexture)
    {
        // �ҵ���������
        FVector2D Center(Canvas->ClipX * 0.52f, Canvas->ClipY * 0.48f);
        // ����ά�Ƚ���һ��ƫ�ƣ�ʹ�������ĺͻ������Ķ���
        FVector2D CrossHairDrawPosition(Center.X - (CrosshairTexture->GetSurfaceWidth() * 0.5f), Center.Y - (CrosshairTexture->GetSurfaceHeight() * 0.5f));

        // �����ĵ����׼��
        FCanvasTileItem TileItem(CrossHairDrawPosition, CrosshairTexture->Resource, FLinearColor::White);
        TileItem.BlendMode = SE_BLEND_Translucent;
        Canvas->DrawItem(TileItem);
    }
}
