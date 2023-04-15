// Fill out your copyright notice in the Description page of Project Settings.


#include "ProxyTestAnimInstance.h"
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

void FBaseAnimInstanceProxy::Update(float DeltaSeconds)
{
	Super::Update(DeltaSeconds);

	if (Owner)
	{
		UE_LOG(LogTemp, Warning, TEXT("Update"));
		//Calculation
		Speed = Velocity.Size();
		ShouldMove = Speed >= 3.0f
			&& !Acceleration.Equals(FVector::ZeroVector);

		// Copy Data
		OwnerAnimInstance->Speed = Speed;
		OwnerAnimInstance->ShouldMove = ShouldMove;
	}
}

void FBaseAnimInstanceProxy::PreUpdate(UAnimInstance* AnimInstance, float DeltaSeconds)
{
	Super::PreUpdate(AnimInstance, DeltaSeconds);

	if (Owner)
	{
		Velocity = CharacterMovement->GetLastUpdateVelocity();
		Acceleration = CharacterMovement->GetCurrentAcceleration();
	}
}

void FBaseAnimInstanceProxy::PostUpdate(UAnimInstance* AnimInstance) const
{
}
