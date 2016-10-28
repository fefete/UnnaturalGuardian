// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "UGAIController.generated.h"

/**
 * 
 */

//PERCEPTION
UCLASS()
class UNNATURALGUARDIAN_API AUGAIController : public AAIController
{
	GENERATED_BODY()
	

  // behaviour tree comp ref
  UBehaviorTreeComponent* beh_comp;

  //--------blackboard--------\\
    //comp ref
  UBlackboardComponent* black_comp;

  //blackboad keys
  UPROPERTY(EditDefaultsOnly, Category = "AI")
    FName location_to_go_key_;
  UPROPERTY(EditDefaultsOnly, Category = "AI")
    FName target_;
  //end blackboard

  //store the points. or fill them up in the unreal editor
  UPROPERTY()
    TArray<AActor*> BotTargetPoints;

  //posess is executed when the char we want to control is spawned. 
  //inside we initialize the blackboad and start the behavior tree
  virtual void Possess(APawn* P) override;
  /*Sets the sensed target in the blackboard*/

public:

  //constructor
  AUGAIController();
  void SetSeenTarget(APawn* Pawn);;

  FORCEINLINE UBlackboardComponent* getBlackboardComp() const { return black_comp; }

  FORCEINLINE TArray<AActor*> getAvaliableTargetPoints() { return BotTargetPoints; }

};
