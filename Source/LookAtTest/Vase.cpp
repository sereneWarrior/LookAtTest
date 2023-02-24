// Fill out your copyright notice in the Description page of Project Settings.


#include "Vase.h"

// Sets default values
AVase::AVase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AVase::Interact_Implementation(ALookAtTestCharacter* interActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Vase"));
}

