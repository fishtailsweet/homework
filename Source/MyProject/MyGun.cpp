// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGun.h"
// Sets default values
AMyGun::AMyGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Gun Mesh"));
}

// Called when the game starts or when spawned
void AMyGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

