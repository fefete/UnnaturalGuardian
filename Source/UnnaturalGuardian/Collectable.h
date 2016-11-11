// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Collectable.generated.h"

UCLASS()
class UNNATURALGUARDIAN_API ACollectable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectable();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintPure, Category = "Collectable")
	bool wasCollected() const { return wasCollected_; }

	UFUNCTION(BlueprintCallable, Category = "Collectable")
	void setCollectedStatus(bool newState);

	//Return the mesh
	FORCEINLINE class UStaticMeshComponent* getMesh() const { return collectableMesh_; };

private:

	//Mesh of the Collectable
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collectable", meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* collectableMesh_;

	bool wasCollected_{ false };

};
