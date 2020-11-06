// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProjectCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

//////////////////////////////////////////////////////////////////////////
// AMyProjectCharacter

AMyProjectCharacter::AMyProjectCharacter()
{
	UserName = "";
	Score = 0;
	PrimaryActorTick.bCanEverTick = true;	// ���ô˽�ɫÿ֡���� Tick()������Ҫʱ�ɽ��˹رգ����������
	// Set size for collision capsule
	
	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 400.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);	// attach���ӵ�RootComponent��CapsuleComponent����
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller������ pawn �����������ת

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // attach���ӵ�CameraBoom������棬Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// InputComponent �Ƕ�����δ����������ݵ������InputComponent �ɸ��ӵ���Ҫ��������� actor
void AMyProjectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// ����"�ƶ�"��
	// ����ִ�и��ദ������������Ȼ��ᷭת��֧�֣������ڽ�����ֵ���ݵ�����ǰͨ���Զ��庯��������е���
	check(PlayerInputComponent);
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyProjectCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMyProjectCharacter::StopJump);


	PlayerInputComponent->BindAxis("MoveForward", this, &AMyProjectCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyProjectCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMyProjectCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMyProjectCharacter::LookUpAtRate);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AMyProjectCharacter::OnResetVR);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyProjectCharacter::Fire);	// �� OnFire ����
	PlayerInputComponent->BindAction("Glass", IE_Pressed, this, &AMyProjectCharacter::OpenGlass);
	PlayerInputComponent->BindAction("Glass", IE_Released, this, &AMyProjectCharacter::CloseGlass);
}


void AMyProjectCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void AMyProjectCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMyProjectCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMyProjectCharacter::MoveForward(float Value)
{
	// ��ȷ�ĸ�������"ǰ��"������¼�����ͼ��˷����ƶ�
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMyProjectCharacter::MoveRight(float Value)
{
	// ��ȷ�ĸ�������"����"������¼�����ͼ��˷����ƶ�
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
void AMyProjectCharacter::BeginPlay()
{
	Super::BeginPlay();

	//if (GEngine)
	//{
		// ��ʾ������Ϣ���롣-1"��"ֵ���׸�������˵������������»�ˢ�´���Ϣ��
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));
	//}
}
void AMyProjectCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AMyProjectCharacter::StartJump()
{
	bPressedJump = true;
}

void AMyProjectCharacter::StopJump()
{
	bPressedJump = false;
}
void AMyProjectCharacter::Fire(){
	// �迼�����㣺�ںδ����ɷ�����ͷ������ࣨ�Ա� Character ����������ͼ�˽����ɺ��ַ����
	// ��Ҫʹ��������ռ�ƫ��ʸ��ȷ�������������λ�á� �轫�˲�����Ϊ�ɱ༭���Ա��� BP_FPSCharacter ��ͼ�н������ú͵����� ���գ��ɻ��ڴ����ݼ��㷢����ĳ�ʼλ��
	// ���Է������塣
	if (BulletClass)
	{
		// ��ȡ������任��
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);
		// �� MuzzleOffset ��������ռ�任������ռ�
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = GetTransform().GetRotation().Rotator();
		MuzzleRotation.Pitch = CameraRotation.Pitch;
		UWorld* World = GetWorld();
		if (World)
		{ 
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();	// instigator���Ǳ����������Ƶ�pawn�������������ָ�������
			// ��ǹ�ڴ����ɷ�����
			FTransform transform;
			transform.SetLocation(MuzzleLocation);
			transform.SetRotation(FQuat(MuzzleRotation));
			AMyBullet* Projectile = World->SpawnActorDeferred<AMyBullet>(BulletClass, transform);
			Projectile->SetScore(&Score);
			Projectile->FinishSpawning(transform);
			if (Projectile)
			{
				// ���÷�����ĳ�ʼ�����
				FVector LaunchDirection = CameraRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}
void AMyProjectCharacter::OpenGlass() {
	FollowCamera->SetRelativeLocation(FVector(340, 0, 0));
}
void AMyProjectCharacter::CloseGlass() {
	FollowCamera->SetRelativeLocation(FVector(0, 0, 0));
}