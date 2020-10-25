// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBullet.h"

// Sets default values
AMyBullet::AMyBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	// 设置球体的碰撞半径。
	CollisionComponent->InitSphereRadius(15.0f);
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Bullet"));	// 在project settings的collision中创建的配置
	// 将碰撞组件设为根组件
	RootComponent = CollisionComponent;	// 模拟将驱动 CollisionComponent，所以将其设为 RootComponent
	CollisionComponent->OnComponentHit.AddDynamic(this, &AMyBullet::OnHit);	// 与碰撞的事件处理函数关联起来
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;	// 勾选 Rotation Follows Velocity 每帧更新其旋转 以匹配速度的方向
	ProjectileMovementComponent->bShouldBounce = false;	// 落地弹起效果
	ProjectileMovementComponent->ProjectileGravityScale = 0;	// 重力为0即射线
	InitialLifeSpan = 1.0f;	// 设置发射物的生命周期
}

// Called when the game starts or when spawned
void AMyBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AMyBullet::FireInDirection(const FVector& ShootDirection)
{	// 只需提供一个发射方向，因为发射物的速度由 ProjectileMovementComponent 定义
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}
void AMyBullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this) {
		float radius = 100 * Hit.GetActor()->GetActorScale3D().Y / 2;	// scale中显示的是倍数，需要乘上模型本身的大小
		for (int i = 1; i <= 5; ++i) {
			if ((pow((Hit.Location.Y - Hit.GetActor()->GetTransform().GetLocation().Y), 2) + pow((Hit.Location.Z - Hit.GetActor()->GetTransform().GetLocation().Z), 2)) <= i * pow(radius, 2) / 5) {
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::FromInt(5 - i + 1));
				break;
			}
		}
		Destroy();
	}
}
