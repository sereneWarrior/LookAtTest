// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseAnimInstance.h"
#include "LookAtTestCharacter.h"
#include "Components/SceneComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"

void UBaseAnimInstance::CheckLookAtRotationRange()
{
	//TODO: Put Direction calculation in Character class?
	FVector currentActorLocation = Owner->GetActorLocation();
	FRotator currentActorRotation = Owner->GetActorRotation();
	
	// Find a rotation for an object at Start location to point at Target location. 
	FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(currentActorLocation, LookAtLocation);
	
	FRotator normalizedRotator = UKismetMathLibrary::NormalizedDeltaRotator(currentActorRotation, lookAtRotation);
	RotationInRange = FMath::Abs(normalizedRotator.Yaw) <= LOOK_AT_ANGLE_OFFSET;
}

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

	// Handle Idle/Walk transition.
	if (CharacterMovement != nullptr)
	{
		Speed = CharacterMovement->Velocity.Size();
	}
	ShouldMove = Speed >= 3.0 && CharacterMovement->GetCurrentAcceleration() != FVector::ZeroVector;

	// Handle Look at behaviour.
	ALookAtTestCharacter* Character = Cast<ALookAtTestCharacter>(Owner);
	if (Character == nullptr) return;

	ToggleLookAt = Character->IsLookingAt;
	if (ToggleLookAt)
	{
		LookAtLocation = Character->LookAtTarget->GetMeshLocation();
		CheckLookAtRotationRange();
	}
}