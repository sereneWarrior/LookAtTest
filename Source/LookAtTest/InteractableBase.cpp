// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableBase.h"

// Sets default values
AInteractableBase::AInteractableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	EnterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EnterMesh"));

	SetRootComponent(Root);
	EnterMesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AInteractableBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteractableBase::MoveToAndPlayAnim(ALookAtTestCharacter* interActor)
{
	float dist = (GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - EnterMesh->GetComponentLocation()).Size();
	float delay = dist / 150.0;
	interActor->MovePlayerTo(EnterMesh->GetComponentLocation(), EnterMesh->GetComponentRotation(), delay);
}

// Called every frame
void AInteractableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

