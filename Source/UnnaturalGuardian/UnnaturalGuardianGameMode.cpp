// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "UnnaturalGuardian.h"
#include "UnnaturalGuardianGameMode.h"
#include "UnnaturalGuardianCharacter.h"
#include "UGAICharacter.h"
#include "kismet/GameplayStatics.h"

AUnnaturalGuardianGameMode::AUnnaturalGuardianGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

}

void AUnnaturalGuardianGameMode::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

}
