// Fill out your copyright notice in the Description page of Project Settings.


#include "Chime.h"

// Sets default values
AChime::AChime()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AChime::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChime::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChime::Interact_Implementation(ALookAtTestCharacter* interActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Chime"));
}
