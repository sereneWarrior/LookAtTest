// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableBase.h"

// Sets default values
AInteractableBase::AInteractableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	EnterMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EnterMesh"));
	
	SetRootComponent(Root);
	EnterMeshComponent->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AInteractableBase::BeginPlay()
{
	Super::BeginPlay();
	EnterMesh = FEnterMesh(EnterMeshComponent);
	UE_LOG(LogTemp, Warning, TEXT("Walk to %s"), *EnterMesh.Location.ToString());
}

// Called every frame
void AInteractableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

