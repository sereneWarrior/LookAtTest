// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LookAtTestCharacter.h"

#include "InteractableBase.generated.h"

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

	void MoveToAndPlayAnim(ALookAtTestCharacter* interActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* EnterMesh;
};
