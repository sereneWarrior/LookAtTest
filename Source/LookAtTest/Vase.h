// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "InteractableBase.h"

#include "Vase.generated.h"

UCLASS()
class LOOKATTEST_API AVase : public AInteractableBase, public IInteractable
{
	GENERATED_BODY()
	
public:	
	AVase();

protected:
	virtual void Interact_Implementation(ALookAtTestCharacter* interActor) override;

};
