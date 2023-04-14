// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Animation/AnimInstanceProxy.h"

#include "BaseAnimInstanceProxy.generated.h"

USTRUCT(BlueprintType)
struct FBaseAnimInstanceProxy : public FAnimInstanceProxy
{
	GENERATED_BODY()
public:
	FBaseAnimInstanceProxy() : FAnimInstanceProxy() {}
	FBaseAnimInstanceProxy(UAnimInstance* Instance);

	virtual void Update(float DeltaSeconds) override

	{

		// Update internal variables

	   // MovementAngle += 1.0f * DeltaSeconds;

		//HorizontalSpeed = FMath::Max(0.0f, HorizontalSpeed - DeltaSeconds);

	}
};

