// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"

#include "Chest.generated.h"

UCLASS()
class LOOKATTEST_API AChest : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Interact_Implementation(ALookAtTestCharacter* interActor) override;
	
	UPROPERTY()
	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* EnterMesh;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
