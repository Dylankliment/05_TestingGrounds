// Fill out your copyright notice in the Description page of Project Settings.

#include "FocusPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"


 EBTNodeResult::Type UFocusPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();	
	BlackboardComp->SetValueAsObject(Enemy.SelectedKeyName, UGameplayStatics::GetPlayerPawn(GetWorld(), 0));	
	OwnerComp.GetAIOwner()->SetFocus(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	return EBTNodeResult::Succeeded;	
}

 //Can use either this way or the other way to find the player controlled pawn, number after getworld stands for which pawn in the possible array of player controllers
 //BlackboardComp->SetValueAsObject(Enemy.SelectedKeyName, GetWorld()->GetFirstPlayerController()->GetPawn());
 //OwnerComp.GetAIOwner()->SetFocus(GetWorld()->GetFirstPlayerController()->GetPawn());  

