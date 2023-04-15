// Fill out your copyright notice in the Description page of Project Settings.

#include "ProxyTestAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"

bool FBaseAnimInstanceProxy::CheckLookAtRotationRange()
{
	//TODO: Put Direction calculation in Character class?
	FVector currentActorLocation = Owner->GetActorLocation();
	FRotator currentActorRotation = Owner->GetActorRotation();
	

	// Find a rotation for an object at Start location to point at Target location. 
	FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(currentActorLocation, LookAtLocation);

	FRotator normalizedRotator = UKismetMathLibrary::NormalizedDeltaRotator(currentActorRotation, lookAtRotation);
	if (FMath::Abs(normalizedRotator.Yaw) <= OwnerAnimInstance->LOOK_AT_ANGLE_OFFSET)
	{
		LookAtLocation = Target->GetMeshLocation();
		return true;
	}
	return false;
}

// Proxy implementation.
void FBaseAnimInstanceProxy::Initialize(UAnimInstance* AnimInstance)
{
	Super::Initialize(AnimInstance);
	if (!AnimInstance) return;

	OwnerAnimInstance = Cast<UProxyTestAnimInstance>(AnimInstance);
	Owner = Cast<ACharacter>(AnimInstance->GetOwningActor());
	
	if (Owner)
	{
		CharacterMovement = Owner->GetCharacterMovement();
	}
}

void FBaseAnimInstanceProxy::PreUpdate(UAnimInstance* AnimInstance, float DeltaSeconds)
{
	Super::PreUpdate(AnimInstance, DeltaSeconds);

	if (Owner)
	{
		Velocity = CharacterMovement->GetLastUpdateVelocity();
		Acceleration = CharacterMovement->GetCurrentAcceleration();
		ALookAtTestCharacter* Character = Cast<ALookAtTestCharacter>(Owner);
		if (Character == nullptr) return;
		if (CharacterIsLookingAt = Character->IsLookingAt
			&& Character->LookAtTarget != nullptr)
		{
			Target = Character->LookAtTarget;
		}
		
	}
}

void FBaseAnimInstanceProxy::Update(float DeltaSeconds)
{
	Super::Update(DeltaSeconds);

	//Calculation
	Speed = Velocity.Size();
	ShouldMove = Speed >= 3.0f
		&& !Acceleration.Equals(FVector::ZeroVector);
	//TODO: REfactor Rotation calculation.
	ToggleLookAt = CharacterIsLookingAt && CheckLookAtRotationRange();
}


void FBaseAnimInstanceProxy::PostUpdate(UAnimInstance* AnimInstance) const
{
	// Copy Data
	if (OwnerAnimInstance)
	{
		OwnerAnimInstance->Speed = Speed;
		OwnerAnimInstance->ShouldMove = ShouldMove;
		OwnerAnimInstance->ToggleLookAt = ToggleLookAt;
		if (ToggleLookAt)
		{
			OwnerAnimInstance->LookAtLocation = LookAtLocation;
		}
	}
}
