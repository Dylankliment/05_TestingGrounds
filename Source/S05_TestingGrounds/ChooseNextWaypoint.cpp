// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "AIController.h"
#include "PatrolRoute.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// TODO Protect against no Subobject
	// TODO Protect against empty Patrol routes

	// Get Patrol Points
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	if (!PatrolRoute) { return EBTNodeResult::Failed; }
		
	auto PatrollingPoints = PatrolRoute->GetPatrolPoints();
	if (PatrollingPoints.Num() == 0) { UE_LOG(LogTemp, Warning, TEXT("No Patrol Route Detected")); return EBTNodeResult::Failed; }


	// Set Next Waypoint
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrollingPoints[Index]);
	
	// Cycle the Index
	auto NextIndex = (Index + 1) % PatrollingPoints.Num();   // Num counts the length/amount of objects in the array AKA Acts like length
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	//UE_LOG(LogTemp, Warning, TEXT("Waypoint index: %i"), Index)
	return EBTNodeResult::Succeeded;
 }
