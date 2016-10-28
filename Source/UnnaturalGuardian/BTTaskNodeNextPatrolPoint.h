// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNodeNextPatrolPoint.generated.h"

/**
 * 
 */
UCLASS()
class UNNATURALGUARDIAN_API UBTTaskNodeNextPatrolPoint : public UBTTaskNode
{
	GENERATED_BODY()
	
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	
};
