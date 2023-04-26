// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "LookAtTarget.h"
#include "Components/TimelineComponent.h"
#include "InteractableBase.h"
#include "LookAtTestCharacter.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayAnimDelegate);

UCLASS(config=Game)
class ALookAtTestCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Interaction Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InterAction;

	void MoveToAndPlayAnim(USkeletalMeshComponent* enterMesh);
	void MoveToAndPlayAnim(FEnterMesh* enterMesh);
	
public:
	ALookAtTestCharacter();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			
	/** Called for looking input */
	void Interact(const FInputActionValue& InputActionValue);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/** Head rotation towards a specific target. **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ALookAtTarget* LookAtTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsLookingAt = false;
	
	/** Interaction flag.**/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsInteracting = false;

	/** Kneeling flag.**/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsKneeling = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UAnimInstance> anim;

	/** Play interaction animations. **/
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void UnlinkAnim();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void LinkAnim();

	UFUNCTION(BlueprintImplementableEvent)
	void MovePlayerTo(FVector newLocation, FRotator otherRot, float duration);

	UPROPERTY(BlueprintCallable, BlueprintAssignable)
	FPlayAnimDelegate OnplayAnim;

	UFUNCTION(BlueprintImplementableEvent)
	void KneelDown();

	UFUNCTION()
	void LinkInteractionAnimLayer();
};

