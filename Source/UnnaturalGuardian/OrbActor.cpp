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
	minScale_.X = (maxScale_.X / 2);// *10;
	minScale_.Y = (maxScale_.Y / 2);// *10;
	minScale_.Z = (maxScale_.Z / 2);// *10;

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
	health_ += 0.25;

	scale_.X += 0.0015;
	scale_.Y += 0.0015;//decreaseScalePercentage_ / 1000;
	scale_.Z += 0.0015;//decreaseScalePercentage_ / 1000;

	//Increase size of actor mesh each tick
	actorMesh_->SetRelativeScale3D(scale_);

	//Cap health to the maxHealth value
	if (health_ >= maxHealth_)
		health_ = maxHealth_;

	//Cap health to the min Value 0 and destroy;
	else if (health_ <= 0.f) {
		health_ = 0.f;
		wasDestoryed_ = true;
		Destroy();
	}

	//Cap the scale to the maxScale value
	if (scale_.X >= maxScale_.X || scale_.Y >= maxScale_.Y || scale_.Z >= maxScale_.Z)
		scale_ = maxScale_;
	else if (scale_.X <= minScale_.X || scale_.Y <= minScale_.Y || scale_.Z <= minScale_.Z)
		scale_ = minScale_;

}

//Set the Active state
void AOrbActor::setActive(bool newState)
{
	isActive_ = newState;
}

void AOrbActor::decreaseHealth()
{
	health_ -= damageDealtByPlayer_;
	//decreaseScalePercentage_ = amount / maxHealth_;

	//Decrease the size of the mesh
	scale_.X -= decreaseScalePercentage_ / maxHealth_;
	scale_.Y -= decreaseScalePercentage_ / maxHealth_;
	scale_.Z -= decreaseScalePercentage_ / maxHealth_;
}

