// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FocusPlayer.generated.h"

/**
 * 
 */
UCLASS()
class S05_TESTINGGROUNDS_API UFocusPlayer : public UBTTaskNode
{
	GENERATED_BODY()
	
public:	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	struct FBlackboardKeySelector Enemy;
	
	
};
