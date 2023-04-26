// Fill out your copyright notice in the Description page of Project Settings.

#include "LookAtTestCharacter.h"
#include "InteractionFinishedNotify.h"

void UInteractionFinishedNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	// Get access to Character Event to unlink from Linked Animation and reactivate movement.
	AActor* AnimOwner = MeshComp->GetOwner();
	if (ALookAtTestCharacter* Character = Cast<ALookAtTestCharacter>(AnimOwner))
	{
		Character->UnlinkAnim();
	}
	//UE_LOG(LogTemp, Warning, TEXT("INTERACTION!!! %s"), *this->GetNotifyName());
}