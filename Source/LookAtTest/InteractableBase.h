// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "InteractableBase.generated.h"

USTRUCT()
struct FEnterMesh
{
	GENERATED_BODY()
	
	FEnterMesh() {};
	FEnterMesh(USkeletalMeshComponent* EnterMeshComponent)
	{
		Location = EnterMeshComponent->GetComponentLocation();
		Rotation = EnterMeshComponent->GetComponentRotation();
	}

	UPROPERTY()
	FVector Location;

	UPROPERTY()
	FRotator Rotation;
};

/*
Base class for objects that need an interaction animation to be played.
*/
UCLASS()
class LOOKATTEST_API AInteractableBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	USceneComponent* Root;


	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* EnterMeshComponent;

	UPROPERTY(EditAnywhere)

	USceneComponent* Socket;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere)
	FName LookAt_Socket = "LookAt";

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAnimInstance> AnimLayer;

	FEnterMesh EnterMesh;
};
