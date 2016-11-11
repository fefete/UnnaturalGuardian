// Fill out your copyright notice in the Description page of Project Settings.

#include "UnnaturalGuardian.h"
#include "Collectable.h"


// Sets default values
ACollectable::ACollectable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create the static mesh component
	collectableMesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Collectable Mesh"));
	RootComponent = collectableMesh_;

}

// Called when the game starts or when spawned
void ACollectable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollectable::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ACollectable::setCollectedStatus(bool newState)
{
	wasCollected_ = newState;
}

