// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Runtime/Engine/Classes/Engine/Canvas.h"
void AMyHUD::DrawHUD()
{
    Super::DrawHUD();

    if (CrosshairTexture)
    {
        // 找到画布中心
        FVector2D Center(Canvas->ClipX * 0.52f, Canvas->ClipY * 0.48f);
        // 纹理维度进行一半偏移，使纹理中心和画布中心对齐
        FVector2D CrossHairDrawPosition(Center.X - (CrosshairTexture->GetSurfaceWidth() * 0.5f), Center.Y - (CrosshairTexture->GetSurfaceHeight() * 0.5f));

        // 在中心点绘制准星
        FCanvasTileItem TileItem(CrossHairDrawPosition, CrosshairTexture->Resource, FLinearColor::White);
        TileItem.BlendMode = SE_BLEND_Translucent;
        Canvas->DrawItem(TileItem);
    }
}
