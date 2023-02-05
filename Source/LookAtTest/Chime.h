// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"

#include "Chime.generated.h"

UCLASS()
class LOOKATTEST_API AChime : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChime();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Interact_Implementation(ALookAtTestCharacter* interActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
