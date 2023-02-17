// Fill out your copyright notice in the Description page of Project Settings.


#include "Chest.h"
#include "Components/SceneComponent.h"

// Sets default values
AChest::AChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	EnterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("EnterMesh"));

	SetRootComponent(Root);
	EnterMesh->SetupAttachment(Root);

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
	//interActor->SetActorTransform(EnterMesh->GetComponentTransform());
	float dist = (GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - EnterMesh->GetComponentLocation()).Size();
	float delay = dist / 150.0;
	interActor->MovePlayerTo(EnterMesh->GetComponentLocation(), EnterMesh->GetComponentRotation(), delay);
	
	// Delay until target location is reached
	FTimerHandle timerHandle;
	
	// Deleagate for call to interaction animation 
	FTimerDelegate playDelegate;
	playDelegate.BindUFunction(interActor, FName("PlayOpenChestAnimation"), EnterMesh->GetComponentLocation());

	GetWorld()->GetTimerManager().SetTimer(timerHandle, playDelegate, delay, false);
	
	
	
	//interActor->PlayOpenChestAnimation(EnterMesh->GetComponentLocation());
}

// Called every frame
void AChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

