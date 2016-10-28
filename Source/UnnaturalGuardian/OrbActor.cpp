// Fill out your copyright notice in the Description page of Project Settings.

#include "UnnaturalGuardian.h"
#include "OrbActor.h"

// Sets default values
AOrbActor::AOrbActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	isActive_ = true;
	maxHealth_ = 100.f;
	health_ = maxHealth_;

	//Create the static mesh component
	actorMesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OrbActor Mesh"));
	RootComponent = actorMesh_;

	maxScale_ = actorMesh_->GetComponentScale();
	scale_ = maxScale_;

	//Set min Scale to be 10% of Max scale
	minScale_.X = (maxScale_.X / 100) * 10;
	minScale_.Y = (maxScale_.Y / 100) * 10;
	minScale_.Z = (maxScale_.Z / 100) * 10;

}

// Called when the game starts or when spawned
void AOrbActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AOrbActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Add health to the Actor each tick
	health_ += 0.5f;

	scale_.X += 0.0015;
	scale_.Y += 0.0015;
	scale_.Z += 0.0015;

	//Increase size of actor mesh each tick
	actorMesh_->SetRelativeScale3D(scale_);

	//Cap health to the maxHealth value
	if (health_ >= maxHealth_)
		health_ = maxHealth_;

	//Cap health to the min Value 0 and destroy;
	else if (health_ <= 0.f) {
		health_ = 0.f;

		UE_LOG(LogTemp, Log, TEXT("Orb Defeated"));

		Destroy();
	}

	//Cap the scale to the maxScale value
	if (scale_.X >= maxScale_.X || scale_.Y >= maxScale_.Y || scale_.Z >= maxScale_.Z)
		scale_ = maxScale_;
	else if (scale_.X <= minScale_.X || scale_.Y <= minScale_.Y || scale_.Z <= minScale_.Z)
		scale_ = minScale_;

	UE_LOG(LogTemp, Log, TEXT("Orb Scale: ,%s"), *actorMesh_->GetComponentScale().ToString());
	//UE_LOG(LogTemp, Log, TEXT("Orb Health: ,%f"), health_);

}

//Set the Active state
void AOrbActor::setActive(bool newState)
{
	isActive_ = newState;
}

void AOrbActor::decreaseHealth(float amount)
{
	health_ -= amount;
	varingPercentage_ = amount / maxHealth_;

	//Decrease the size of the mesh
	scale_.X -= varingPercentage_;
	scale_.Y -= varingPercentage_;
	scale_.Z -= varingPercentage_;

}

void AOrbActor::wasDefeated()
{
	UE_LOG(LogTemp, Log, TEXT("Orb Defeated"));

	Destroy();
}

