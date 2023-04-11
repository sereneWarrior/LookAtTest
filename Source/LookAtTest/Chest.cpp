// Fill out your copyright notice in the Description page of Project Settings.


#include "Chest.h"
#include "Components/SceneComponent.h"

// Sets default values
AChest::AChest()
{
}

void AChest::Interact_Implementation(ALookAtTestCharacter* interActor)
{
	UE_LOG(LogTemp, Warning, TEXT("chest"));
	interActor->OnplayAnim.AddDynamic(interActor, &ALookAtTestCharacter::PlayOpenChestAnimation);
	MoveToAndPlayAnim(interActor);
}


