// Copyright Epic Games, Inc. All Rights Reserved.

#include "MultiTPPGameMode.h"
#include "MultiTPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMultiTPPGameMode::AMultiTPPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
