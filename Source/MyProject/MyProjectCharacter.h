// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyBullet.h"
#include "MyGun.h"
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

	// EditDefaultsOnly ˵������ζ�ŷ�������ֻ������ͼ�ϱ���ΪĬ�ϣ�����������ͼ��ÿ��ʵ��������
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
	UFUNCTION()	// ʹ�����˽���Щ�������Ա㽫���Ǽ������л����������湦��
	void MoveForward(float Value);	// ����ǰ���ͺ��˵�����

	/** Called for side to side input */
	UFUNCTION()	// ���������ƶ�������
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
	// APawn interface�����ú󽫹��ܰ󶨵�����
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface
	virtual void BeginPlay() override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	// ÿ֡����
	virtual void Tick(float DeltaTime) override;
	// ���°���ʱ������Ծ���
	UFUNCTION()
	void StartJump();
	// �ɿ�����ʱ�����Ծ���
	UFUNCTION()
	void StopJump();
	void Fire();	// ������ĺ���
	// ��ͨ�� EditAnywhere ˵��������ͼ�༭����Ĭ��ģʽ���ɫ����ʵ���� Details ��ǩ���޸�ǹ��ƫ��ֵ��ֻ������public��Ա��
	// ��ͨ�� BlueprintReadWrite ˵������ȡ��������ͼ�е�ǹ��ƫ��ֵ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;	// �������λ�õ�ǹ��ƫ��
};

