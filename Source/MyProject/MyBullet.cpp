// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBullet.h"

// Sets default values
AMyBullet::AMyBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	// �����������ײ�뾶��
	CollisionComponent->InitSphereRadius(15.0f);
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Bullet"));	// ��project settings��collision�д���������
	// ����ײ�����Ϊ�����
	RootComponent = CollisionComponent;	// ģ�⽫���� CollisionComponent�����Խ�����Ϊ RootComponent
	CollisionComponent->OnComponentHit.AddDynamic(this, &AMyBullet::OnHit);	// ����ײ���¼���������������
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;	// ��ѡ Rotation Follows Velocity ÿ֡��������ת ��ƥ���ٶȵķ���
	ProjectileMovementComponent->bShouldBounce = false;	// ��ص���Ч��
	ProjectileMovementComponent->ProjectileGravityScale = 0;	// ����Ϊ0������
	InitialLifeSpan = 1.0f;	// ���÷��������������
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
{	// ֻ���ṩһ�����䷽����Ϊ��������ٶ��� ProjectileMovementComponent ����
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}
void AMyBullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this) {
		float radius = 100 * Hit.GetActor()->GetActorScale3D().Y / 2;	// scale����ʾ���Ǳ�������Ҫ����ģ�ͱ���Ĵ�С
		for (int i = 1; i <= 5; ++i) {
			if ((pow((Hit.Location.Y - Hit.GetActor()->GetTransform().GetLocation().Y), 2) + pow((Hit.Location.Z - Hit.GetActor()->GetTransform().GetLocation().Z), 2)) <= i * pow(radius, 2) / 5) {
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::FromInt(5 - i + 1));
				break;
			}
		}
		Destroy();
	}
}
