// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyBullet.h"
#include "Runtime/Engine/Classes/Engine/SkeletalMeshSocket.h" 
#include "MyProjectCharacter.generated.h"

UCLASS(config=Game)
class AMyProjectCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	// EditDefaultsOnly 说明符意味着发射物类只能在蓝图上被设为默认，而不能在蓝图的每个实例上设置
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AActor> BulletClass;

public:
	AMyProjectCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;
protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	UFUNCTION()	// 使引擎了解这些函数，以便将它们加入序列化和其他引擎功能
	void MoveForward(float Value);	// 处理前进和后退的输入

	/** Called for side to side input */
	UFUNCTION()	// 处理左右移动的输入
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface，调用后将功能绑定到输入
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface
	virtual void BeginPlay() override;
	// 弹簧臂是连接摄像机（或其他组件）的简便方式，因此其不会过于僵硬，移动时也更加流畅
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	// 每帧调用
	virtual void Tick(float DeltaTime) override;
	// 按下按键时设置跳跃标记
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void StartJump();
	// 松开按键时清除跳跃标记
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void StopJump();
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Fire();	// 处理开火的函数
	// 可通过 EditAnywhere 说明符在蓝图编辑器的默认模式或角色任意实例的 Details 标签中修改枪口偏移值（只能用于public成员）
	// 可通过 BlueprintReadWrite 说明符获取并设置蓝图中的枪口偏移值
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void OpenGlass();	
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void CloseGlass();	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;	// 从摄像机位置的枪口偏移
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int Score;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FString UserName;
};

