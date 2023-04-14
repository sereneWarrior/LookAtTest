// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseAnimInstanceProxy.h"
#include "ProxyTestAnimInstance.generated.h"

/**
 * 
 */
UCLASS(Transient, Blueprintable)
class LOOKATTEST_API UProxyTestAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	UPROPERTY(Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FBaseAnimInstanceProxy Proxy;

	virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override
	{

		// override this to just return the proxy on this instance

		return &Proxy;

	}
	virtual void DestroyAnimInstanceProxy(FAnimInstanceProxy* InProxy) override

	{

	}

	friend struct FBaseAnimInstanceProxy;

};
