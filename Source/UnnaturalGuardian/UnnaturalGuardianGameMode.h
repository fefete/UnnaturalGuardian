// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "UnnaturalGuardianGameMode.generated.h"

UCLASS(minimalapi)
class AUnnaturalGuardianGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AUnnaturalGuardianGameMode();

	virtual void Tick(float DeltaSeconds) override;


private:
	//class AUnnaturalGuardianCharacter* playerCharacter_;
	//class AUGAICharacter* enemy_; //This will need to be an array of enemies
};



