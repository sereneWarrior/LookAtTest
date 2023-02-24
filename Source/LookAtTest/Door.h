// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "InteractableBase.h"

#include "Door.generated.h"

UCLASS()
class LOOKATTEST_API ADoor : public AInteractableBase, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	virtual void Interact_Implementation(ALookAtTestCharacter* interActor) override;

};
