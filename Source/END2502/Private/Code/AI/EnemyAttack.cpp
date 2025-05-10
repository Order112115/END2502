// Fill out your copyright notice in the Description page of Project Settings.

#include "AIController.h"
#include "Example/ExampleActorWithInterfaces.h"
#include "EngineUtils.h"
#include "Code/AI/EnemyAttack.h"
#include "Code/Actors/BaseAgent.h"


EBTNodeResult::Type UEnemyAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
        I->EnemyAttack();

      
    }

    if (MessageName != NAME_None)
    {
        OwnerComp.RegisterMessageObserver(this, MessageName);
    }

    return EBTNodeResult::InProgress;  // Ensure a return value for the case where I is null
}
