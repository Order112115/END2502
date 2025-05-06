// Fill out your copyright notice in the Description page of Project Settings.

#include "AIController.h"
#include "NavigationSystem.h"
#include "Code/AI/FindLocation.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/BlackboardComponent.h"


UFindLocation::UFindLocation()
{
    
    LocationKey.SelectedKeyName = "Location";
}


EBTNodeResult::Type UFindLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AICon = OwnerComp.GetAIOwner();
    if (!AICon) return EBTNodeResult::Failed;

    APawn* Pawn = AICon->GetPawn();
    if (!Pawn) return EBTNodeResult::Failed;

    UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
    if (!NavSys) return EBTNodeResult::Failed;

    FVector Origin = Pawn->GetActorLocation();
    FNavLocation RandomPoint;

    if (NavSys->GetRandomReachablePointInRadius(Origin, SearchRadius, RandomPoint))
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(LocationKey.SelectedKeyName, RandomPoint.Location);
        return EBTNodeResult::Succeeded;
    }

    return EBTNodeResult::Failed;
}