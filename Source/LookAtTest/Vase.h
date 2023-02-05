// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"

#include "Vase.generated.h"

UCLASS()
class LOOKATTEST_API AVase : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Interact_Implementation(ALookAtTestCharacter* interActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
