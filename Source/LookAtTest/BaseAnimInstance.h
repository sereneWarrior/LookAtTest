// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "BaseAnimInstance.generated.h"

UCLASS()
class LOOKATTEST_API UBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	void CheckLookAtRotationRange();
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadWrite)
	float Speed;

	UPROPERTY(BlueprintReadWrite)
	bool ShouldMove;

	UPROPERTY(BlueprintReadWrite)
	FVector LookAtLocation;

	UPROPERTY(BlueprintReadOnly)
	bool RotationInRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LOOK_AT_ANGLE_OFFSET = 80.0;

	UPROPERTY(BlueprintReadOnly)
	bool ToggleLookAt = false;

	UPROPERTY(BlueprintReadWrite)
	ACharacter* Owner;

	UPROPERTY(BlueprintReadWrite)
	UCharacterMovementComponent* CharacterMovement;
};
 