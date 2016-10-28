// Fill out your copyright notice in the Description page of Project Settings.

#include "UnnaturalGuardian.h"
#include "UGBotTargetPoint.h"
#include "UGAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BTTaskNodeNextPatrolPoint.h"




EBTNodeResult::Type UBTTaskNodeNextPatrolPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{

  AUGAIController* AICon = Cast<AUGAIController>(OwnerComp.GetAIOwner());

  //if the controller is valid
  //1 get the blacboard comp and the current point of the bot
  //2 search for the next point, wich will be differenmt fron the current
    if (AICon)
    {

      UBlackboardComponent* BlackboardComp = AICon->getBlackboardComp();
      AUGBotTargetPoint* CurrentPoint = Cast<AUGBotTargetPoint>(BlackboardComp->GetValueAsObject("LocationToGo"));

      TArray<AActor*> AvailableTargetPoints = AICon->getAvaliableTargetPoints();

      //This variable will contain a random index in order to determine the next possible point
      int32 RandomIndex;

      //Here, we store the possible next target point
      AUGBotTargetPoint* NextTargetPoint = nullptr;

      //Find a next point which is different from the current one
      do
      {
        RandomIndex = FMath::RandRange(0, AvailableTargetPoints.Num() - 1);
        //Remember that the Array provided by the Controller function contains AActor* objects so we need to cast.
        NextTargetPoint = Cast<AUGBotTargetPoint>(AvailableTargetPoints[RandomIndex]);
      } while (CurrentPoint == NextTargetPoint);

      //Update the next location in the Blackboard so the bot can move to the next Blackboard value
      BlackboardComp->SetValueAsObject("LocationToGo", NextTargetPoint);

      //At this point, the task has been successfully completed
      return EBTNodeResult::Succeeded;
    }
    return EBTNodeResult::Failed;
 }
