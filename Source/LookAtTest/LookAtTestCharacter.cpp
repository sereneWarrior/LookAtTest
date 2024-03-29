// Copyright Epic Games, Inc. All Rights Reserved.

#include "LookAtTestCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interactable.h"

#include "Kismet/KismetMathLibrary.h"


//////////////////////////////////////////////////////////////////////////
// ALookAtTestCharacter

ALookAtTestCharacter::ALookAtTestCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ALookAtTestCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ALookAtTestCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

//////////////////////////////////////////////////////////////////////////
// Input

void ALookAtTestCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALookAtTestCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ALookAtTestCharacter::Look);

		//Ineracting
		EnhancedInputComponent->BindAction(InterAction, ETriggerEvent::Completed, this, &ALookAtTestCharacter::Interact);

	}

}

void ALookAtTestCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ALookAtTestCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ALookAtTestCharacter::Interact(const FInputActionValue& InputActionValue)
{
	// TODO: Improve where it is called. If Kneeling is moved at some point it needs change.
	TArray<AActor*> otherActors;
	GetOverlappingActors(otherActors, AInteractableBase::StaticClass());
	// Trigger interaction animation
	if (!otherActors.IsEmpty())
	{
		AInteractableBase* interactableObj = Cast<AInteractableBase>(otherActors[0]);
		InteractionAnimInstance = interactableObj->AnimLayer;
		MoveToAndPlayAnim(&interactableObj->EnterMesh);
		//IInteractable::Execute_Interact(otherActors[0], this);
		return;
	}
	// Trigger kneeling
	UE_LOG(LogTemp, Warning, TEXT("Kneel"));
	KneelDown();
}

// @todo DEPRECATED
void ALookAtTestCharacter::MoveToAndPlayAnim(USkeletalMeshComponent* enterMesh)
{
	float dist = (GetActorLocation() - enterMesh->GetComponentLocation()).Size();
	// TODO: Put 105.0 (max speed) into varoable filled by mov comp.
	float delay = dist / 150.0;
	MovePlayerTo(enterMesh->GetComponentLocation(), enterMesh->GetComponentRotation(), delay);
}

void ALookAtTestCharacter::MoveToAndPlayAnim(FEnterMesh* enterMesh)
{
	float dist = (GetActorLocation() - enterMesh->Location).Size();
	// TODO: Put 150.0 (max speed) into varoable filled by mov comp.
	float delay = dist / GetCharacterMovement()->MaxWalkSpeed;
	MovePlayerTo(enterMesh->Location, enterMesh->Rotation, delay);
}

void ALookAtTestCharacter::LinkInteractionAnimLayer()
{
	GetMesh()->LinkAnimClassLayers(InteractionAnimInstance);
	GetController()->SetIgnoreMoveInput(true);
}

void ALookAtTestCharacter::UnlinkInteractionAnimLayer()
{
	GetMesh()->UnlinkAnimClassLayers(InteractionAnimInstance);
	GetController()->SetIgnoreMoveInput(false);
}