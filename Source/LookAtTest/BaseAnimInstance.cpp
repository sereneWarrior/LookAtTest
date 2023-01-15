// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseAnimInstance.h"

void UBaseAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Owner = Cast<ACharacter>(GetOwningActor());
	if (Owner != nullptr)
	{
		CharacterMovement = Cast<UCharacterMovementComponent>(Owner->GetMovementComponent());
	}
}

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (CharacterMovement != nullptr)
	{
		Speed = CharacterMovement->Velocity.Size();
	}
	ShouldMove = Speed >= 3.0 && CharacterMovement->GetCurrentAcceleration() != FVector::ZeroVector;
}