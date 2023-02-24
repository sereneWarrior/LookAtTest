// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "InteractableBase.h"

#include "Chest.generated.h"

UCLASS()
class LOOKATTEST_API AChest : public AInteractableBase, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChest();

protected:

	virtual void Interact_Implementation(ALookAtTestCharacter* interActor) override;
};
