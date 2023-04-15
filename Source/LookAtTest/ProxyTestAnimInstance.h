// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstanceProxy.h"
#include "LookAtTestCharacter.h"

#include "ProxyTestAnimInstance.generated.h"

class UProxyTestAnimInstance;

USTRUCT(BlueprintType)
struct LOOKATTEST_API FBaseAnimInstanceProxy : public FAnimInstanceProxy
{
	GENERATED_BODY()

	bool CheckLookAtRotationRange();
protected:
	
	// Called on AnimInstance initialisation.
	virtual void Initialize(UAnimInstance* AnimInstance) override;
	// Runs on Anim thread, does calculations and updates varaibles inside proxy.
	virtual void Update(float DeltaSeconds) override;
	// Called on gamethrerad before update, to copy any game data into proxy (anim instance, character, world etc.)
	virtual void PreUpdate(UAnimInstance* AnimInstance, float DeltaSeconds) override;
	//Called on game thread, after update to copy updated data into anim instance
	virtual void PostUpdate(UAnimInstance* AnimInstance) const override;

	//General
	UPROPERTY(Transient)
	UProxyTestAnimInstance* OwnerAnimInstance;

	UPROPERTY(Transient, BlueprintReadOnly)
		ACharacter* Owner;

	UPROPERTY(Transient, BlueprintReadOnly)
		UCharacterMovementComponent* CharacterMovement;

	//Movement
	UPROPERTY(Transient, BlueprintReadOnly)
		float Speed;

	UPROPERTY(Transient, BlueprintReadOnly)
		FVector Velocity;

	UPROPERTY(Transient, BlueprintReadOnly)
		FVector Acceleration;

	UPROPERTY(Transient, BlueprintReadOnly)
		bool ShouldMove;

	//Head rotation
	UPROPERTY(Transient, BlueprintReadOnly)
		FVector LookAtLocation;

	UPROPERTY(Transient, BlueprintReadOnly)
		bool RotationInRange;

	UPROPERTY(Transient, BlueprintReadOnly)
		bool ToggleLookAt = false;

	UPROPERTY(Transient, BlueprintReadOnly)
		bool CharacterIsLookingAt = false;

	UPROPERTY(Transient, BlueprintReadOnly)
		ALookAtTarget* Target;
};


UCLASS()
class LOOKATTEST_API UProxyTestAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	friend struct FBaseAnimInstanceProxy;

protected:
	UPROPERTY(Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FBaseAnimInstanceProxy Proxy;

	virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override {	return &Proxy;	}
	virtual void DestroyAnimInstanceProxy(FAnimInstanceProxy* InProxy) override {}

	// Movement
	UPROPERTY(Transient, EditAnywhere, BlueprintReadOnly)
		float Speed;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadOnly)
		FVector Velocity;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadOnly)
		FVector Acceleration;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadOnly)
		bool ShouldMove;

	// Head rotation
	UPROPERTY(Transient, EditAnywhere, BlueprintReadOnly)
		FVector LookAtLocation;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadOnly)
		float LOOK_AT_ANGLE_OFFSET = 80.0;

	UPROPERTY(Transient, EditAnywhere, BlueprintReadOnly)
		bool ToggleLookAt = false;
};