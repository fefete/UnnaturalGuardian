// Fill out your copyright notice in the Description page of Project Settings.

#include "UnnaturalGuardian.h"
#include "UGAICharacter.h"
#include "UGAIController.h"
#include "UnnaturalGuardianCharacter.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
AUGAICharacter::AUGAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
  PrimaryActorTick.bCanEverTick = true;
  pawn_sensing_component_ = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Pawn sensing comp"));
  pawn_sensing_component_->bEnableSensingUpdates = true;
  
  pawn_sensing_component_->SetPeripheralVisionAngle(sensing_degrees_);
}

// Called when the game starts or when spawned
void AUGAICharacter::BeginPlay()
{
	Super::BeginPlay();
  if (pawn_sensing_component_) {
    pawn_sensing_component_->OnSeePawn.AddDynamic(this, &AUGAICharacter::onSeePlayer);
  }
  ai_controller = Cast<AUGAIController>(GetController());
}

// Called every frame
void AUGAICharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	AUnnaturalGuardianCharacter* playerCharacter_ = Cast<AUnnaturalGuardianCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	pawn_sensing_component_->SightRadius = sightRadius_;

	if (playerCharacter_) {
		if (canSeePlayer_ == true) {

			playerCharacter_->decreasePlayerHealth(0.1f);

		}
		else if (playerCharacter_->isPlayerInStealthMode() == true) {
			sightRadius_ = 750.0f;
		}
		else {
			sightRadius_ = 1500.f;
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Sight Radius: %f"), sightRadius_);

}

// Called to bind functionality to input
void AUGAICharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void AUGAICharacter::onSeePlayer(APawn * p)
{
  if (ai_controller) {
    ai_controller->SetSeenTarget(p);
  }
}

void AUGAICharacter::setCanSeePlayer(bool state)
{
	canSeePlayer_ = state;
}

void AUGAICharacter::setSightRadius(float newRadius)
{
	sightRadius_ = newRadius;
}

