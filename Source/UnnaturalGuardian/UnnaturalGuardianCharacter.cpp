// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "UnnaturalGuardian.h"
#include "UnnaturalGuardianCharacter.h"
#include "UGAICharacter.h"
#include "Collectable.h"
#include "OrbActor.h"

//////////////////////////////////////////////////////////////////////////
// AUnnaturalGuardianCharacter

AUnnaturalGuardianCharacter::AUnnaturalGuardianCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	// Create Sphere Collider
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	SphereCollider->SetupAttachment(RootComponent);
	SphereCollider->SetSphereRadius(200);

	//Set Initial health values
	maxHealth_ = 125.0;
	playerCurrentHealth_ = maxHealth_;

}

//////////////////////////////////////////////////////////////////////////
// Input

void AUnnaturalGuardianCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// Set up gameplay key bindings
	check(InputComponent);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//InputComponent->BindAction("Stealth", IE_Pressed, this, &AUnnaturalGuardianCharacter::enableStealthMode);
	//InputComponent->BindAction("Stealth", IE_Released, this, &AUnnaturalGuardianCharacter::disableStealthMode);


	InputComponent->BindAction("DestroyEnemy", IE_Released, this, &AUnnaturalGuardianCharacter::destroyEnemy);
	InputComponent->BindAction("DestroyOrb", IE_Released, this, &AUnnaturalGuardianCharacter::destoryOrb);
	//InputComponent->BindAction("CollectCollectable", IE_Released, this, &AUnnaturalGuardianCharacter::collectCollectable);

	InputComponent->BindAxis("MoveForward", this, &AUnnaturalGuardianCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AUnnaturalGuardianCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &AUnnaturalGuardianCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &AUnnaturalGuardianCharacter::LookUpAtRate);

	// handle touch devices
	InputComponent->BindTouch(IE_Pressed, this, &AUnnaturalGuardianCharacter::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &AUnnaturalGuardianCharacter::TouchStopped);

}


void AUnnaturalGuardianCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	// jump, but only on the first touch
	if (FingerIndex == ETouchIndex::Touch1)
	{
		Jump();
	}
}

void AUnnaturalGuardianCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (FingerIndex == ETouchIndex::Touch1)
	{
		StopJumping();
	}
}

void AUnnaturalGuardianCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AUnnaturalGuardianCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AUnnaturalGuardianCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AUnnaturalGuardianCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AUnnaturalGuardianCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (playerCurrentHealth_ < 0)
		//Destroy();

	if (playerCurrentHealth_ < maxHealth_) {
		playerCurrentHealth_ += 0.010f;
	}

}

void AUnnaturalGuardianCharacter::decreasePlayerHealth(float amount)
{
	playerCurrentHealth_ -= amount;

	//Call health change effect
	healthChangeEffect();
}

void AUnnaturalGuardianCharacter::addPlayerHealth(float amount)
{
	playerCurrentHealth_ += amount;
}

void AUnnaturalGuardianCharacter::enableStealthMode()
{
	isStealthed_ = true;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
}

void AUnnaturalGuardianCharacter::disableStealthMode()
{
	isStealthed_ = false;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void AUnnaturalGuardianCharacter::destroyEnemy()
{

	//Get All Colliding Actors and store them in an array
	TArray<AActor *> CollidingActors;
	SphereCollider->GetOverlappingActors(CollidingActors);

	for (int32 i = 0; i < CollidingActors.Num(); ++i) {

		//Cast the actor to ai enemy  
		AUGAICharacter* const enemy = Cast<AUGAICharacter>(CollidingActors[i]);

		//If cast is succesful and MyActor is active
		if (enemy && !enemy->IsPendingKill() && enemy->canSeePlayer() == false && isStealthed_ == true) {

			//enemy->Destroy();

		}

	}

}

void AUnnaturalGuardianCharacter::destoryOrb()
{
	//Get All Colliding Actors and store them in an array
	TArray<AActor *> CollidingActors;
	SphereCollider->GetOverlappingActors(CollidingActors);

	for (int32 i = 0; i < CollidingActors.Num(); ++i) {

		//Cast the actor to OrbActor
		AOrbActor* const orbActor = Cast<AOrbActor>(CollidingActors[i]);

		//If cast is succesful and OrbActor is active
		if (orbActor && !orbActor->IsPendingKill() && orbActor->isActive()) {

			//orbActor->decreaseHealth();

		}

	}
}
