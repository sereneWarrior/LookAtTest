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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ShouldMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector LookAtLocation;

	UPROPERTY(BlueprintReadOnly)
	bool RotationInRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LOOK_AT_ANGLE_OFFSET = 80.0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool ToggleLookAt = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ACharacter* Owner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCharacterMovementComponent* CharacterMovement;

	
	
};
 