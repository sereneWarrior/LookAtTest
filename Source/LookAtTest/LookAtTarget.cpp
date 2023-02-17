// Fill out your copyright notice in the Description page of Project Settings.

#include "LookAtTarget.h"
#include "LookAtTestCharacter.h"
#include "Components/BoxComponent.h"

// Sets default values
ALookAtTarget::ALookAtTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	
	SetRootComponent(Root);
	StaticMeshComponent->SetupAttachment(Root);
	
	Trigger = CreateDefaultSubobject<UBoxComponent>(FName("Triggerl"));
	Trigger->SetBoxExtent(FVector(10.0f, 10.0f, 10.0f));
	Trigger->SetupAttachment(StaticMeshComponent);
	//Trigger->SetRelativeLocation(FVector(0.0f, 0.0f, 100.0f));
}

// Called when the game starts or when spawned
void ALookAtTarget::BeginPlay()
{
	Super::BeginPlay();

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ALookAtTarget::OnOverlapBegin);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &ALookAtTarget::OnOverlapEnd);
}

void ALookAtTarget::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ALookAtTestCharacter* Character = Cast< ALookAtTestCharacter>(OtherActor);

	Character->IsLookingAt = true;
	Character->LookAtTarget = this;
}

void ALookAtTarget::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ALookAtTestCharacter* Character = Cast< ALookAtTestCharacter>(OtherActor);

	Character->IsLookingAt = false;
}