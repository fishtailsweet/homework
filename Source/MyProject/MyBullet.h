// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include <Runtime\Engine\Classes\GameFramework\ProjectileMovementComponent.h>
#include "MyBullet.generated.h"		// ���������һ����include��

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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void FireInDirection(const FVector& ShootDirection);	// �ڷ��䷽�������÷�������ٶȵĺ���
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);	
	// �ӵ���������ʱ���õĺ���
	// ������ײ���
	UPROPERTY(VisibleDefaultsOnly, Category = Bullet)
	USphereComponent* CollisionComponent;
	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;	// �������˶����
private:
};
