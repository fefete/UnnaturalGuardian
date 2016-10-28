// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "OrbActor.generated.h"

UCLASS()
class UNNATURALGUARDIAN_API AOrbActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AOrbActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//Return the mesh
	FORCEINLINE class UStaticMeshComponent* getMesh() const { return actorMesh_; };

	UFUNCTION(BlueprintPure, Category = "OrbActor")
		bool isActive() const { return isActive_; };

	UFUNCTION(BlueprintCallable, Category = "OrbActor")
		void setActive(bool newState);

	// TOCALL: when 'Orb' is Destroyed
	void wasDefeated();

	//TOCALL: when decreasing the health of the actor (orb)
	void decreaseHealth(float amount);
	float getHealth() const { return health_; };

protected:

	bool isActive_;

	float health_;
	float maxHealth_;

	float varingPercentage_;

	FVector scale_;
	FVector maxScale_;
	FVector minScale_;

private:

	//Mesh of the actor in the level
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "OrbActor", meta = (AllowPrivateAccess = true))
		class UStaticMeshComponent* actorMesh_;

	
	
};
