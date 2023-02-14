// Fill out your copyright notice in the Description page of Project Settings.


#include "Chest.h"

// Sets default values
AChest::AChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AChest::BeginPlay()
{
	Super::BeginPlay();
	
}

void AChest::Interact_Implementation(ALookAtTestCharacter* interActor)
{
	// TODO: Check if IsInteractingflag is set.
	UE_LOG(LogTemp, Warning, TEXT("Chest"));
	interActor->PlayOpenChestAnimation();
}

// Called every frame
void AChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

