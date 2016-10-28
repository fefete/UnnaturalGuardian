// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "UGAICharacter.generated.h"

UCLASS()
class UNNATURALGUARDIAN_API AUGAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUGAICharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* BehaviorTree;
	UPROPERTY(EditAnywhere, Category = "AI")
	class AUGAIController* ai_controller;

	/*The Component which is used for the "seeing" sense of the AI*/
	UPROPERTY(VisibleAnywhere, Category = "AI")
	class UPawnSensingComponent* pawn_sensing_component_;

	UPROPERTY(EditAnywhere, Category = "AI")
	float sensing_degrees_;

	UPROPERTY(EditAnywhere, Category = "Patrolling")
	TArray<AActor*> BotPatrollingPoints;
	
	UFUNCTION()
	void onSeePlayer(APawn* p);

	//Returns canSeePlayer bool  
	UFUNCTION(BlueprintPure, Category = "AI")
	bool canSeePlayer() const { return canSeePlayer_; };

	//Sets canSeePlayer bool, true when ai can see, false when ai cant 
	UFUNCTION(BlueprintCallable, Category = "AI")
	void setCanSeePlayer(bool playerSeen);

	//Returns the current sightRaduis float  
	UFUNCTION(BlueprintPure, Category = "AI")
	float getSightRaduis() const { return sightRadius_; };

	//Sets the Ai sight radius float
	UFUNCTION(BlueprintCallable, Category = "AI")
	void setSightRadius(float newRadius);



private:

	bool canSeePlayer_{ false };

	float sightRadius_{ 1500.f };

};
