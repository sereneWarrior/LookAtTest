// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "LookAtTarget.h"
#include "Components/TimelineComponent.h"
#include "LookAtTestCharacter.generated.h"

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

	FTimeline CurveTimeline;

	UPROPERTY(EditAnywhere)
	UCurveFloat* CurveRot;

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

	/** Play interaction animations. **/
	UFUNCTION(BlueprintImplementableEvent)
	void PlayOpenDoorAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayOpenChestAnimation(FVector newLocation);

	UFUNCTION(BlueprintImplementableEvent)
	void MovePlayerTo(FVector newLocation, FRotator otherRot, float duration);

	UFUNCTION(BlueprintImplementableEvent)
	void KneelDown();

	void InteractDoor();

	void RotateTo(FRotator target);

	UFUNCTION()
	void RotationUpdate(float value);

	void DoTimeline(USkeletalMeshComponent* EnterMesh);

private:

	FRotator Start;

	FRotator End;
};

