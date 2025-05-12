// Fill out your copyright notice in the Description page of Project Settings.

#include "AIController.h"
#include "EngineUtils.h"
#include "Code/Actors/BaseAgent.h"
#include "Code/AI/EnemyReload.h"

EBTNodeResult::Type UEnemyReload::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AAIController* AICon = OwnerComp.GetAIOwner();
    if (!AICon)
    {
        return EBTNodeResult::Failed;
    }

    APawn* Pawn = AICon->GetPawn();
    if (!Pawn)
    {
        return EBTNodeResult::Failed;
    }

    IEnemyInterface* I = Cast<IEnemyInterface>(Pawn);

    if (I)
    {
        I->EnemyReload();


    }

    if (MessageName != NAME_None)
    {
        OwnerComp.RegisterMessageObserver(this, MessageName);
    }

    return EBTNodeResult::InProgress;
}
