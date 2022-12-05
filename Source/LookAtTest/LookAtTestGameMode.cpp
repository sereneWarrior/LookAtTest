// Copyright Epic Games, Inc. All Rights Reserved.

#include "LookAtTestGameMode.h"
#include "LookAtTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALookAtTestGameMode::ALookAtTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
