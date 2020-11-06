// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include <Runtime\Engine\Classes\GameFramework\ProjectileMovementComponent.h>
#include "MyBullet.generated.h"		// 必须是最后一个被include的

UCLASS()
class MYPROJECT_API AMyBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyBullet();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	int *SumScore;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void FireInDirection(const FVector& ShootDirection);	// 在发射方向上设置发射物初速度的函数
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);	
	// 子弹命中物体时调用的函数
	// 球体碰撞组件
	UPROPERTY(VisibleDefaultsOnly, Category = Bullet)
	USphereComponent* CollisionComponent;
	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;	// 发射物运动组件
	void SetScore(int *Sum);
};
