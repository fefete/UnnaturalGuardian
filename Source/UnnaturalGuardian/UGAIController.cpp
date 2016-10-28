// Fill out your copyright notice in the Description page of Project Settings.

#include "UnnaturalGuardian.h"
#include "UGAIController.h"
#include "UGAICharacter.h"
#include "UGBotTargetPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"


AUGAIController::AUGAIController()
{
  beh_comp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));
  black_comp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
  location_to_go_key_ = "LocationToGo";
  target_ = "Target";
}

void AUGAIController::Possess(APawn * p)
{
  Super::Possess(p);

  //get the possessed character and check if its my own AI char
  AUGAICharacter* AIChar = Cast<AUGAICharacter>(p);
  AIChar->bCollideWhenPlacing = true;
  if (AIChar)
  {

    //if the blackboard is valid initialize the blackboard for the corresponding tree
    if (AIChar->BehaviorTree->BlackboardAsset) {
      black_comp->InitializeBlackboard(*(AIChar->BehaviorTree->BlackboardAsset));
    }

    for (int i = 0; i < AIChar->BotPatrollingPoints.Num(); i++) {
      BotTargetPoints.Emplace(AIChar->BotPatrollingPoints[i]);
    }

    //Start the behavior tree which corresponds to the specific character
    beh_comp->StartTree(*AIChar->BehaviorTree);
  }


}

void AUGAIController::SetSeenTarget(APawn * Pawn)
{
  if (black_comp)
  {
    black_comp->SetValueAsObject(target_, Pawn);
  }
}


