// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

// Sets default values
ADoor::ADoor()
{

}

void ADoor::Interact_Implementation(ALookAtTestCharacter* interActor)
{
	// Binf the right animation to the players OnPlayAim delegate
	interActor->OnplayAnim.AddDynamic(interActor, &ALookAtTestCharacter::PlayOpenDoorAnimation);
	MoveToAndPlayAnim(interActor);
}
