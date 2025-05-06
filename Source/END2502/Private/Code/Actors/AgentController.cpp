// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/AgentController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"

AAgentController::AAgentController()
{
    AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
    SetPerceptionComponent(*AIPerceptionComponent);
   
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
    SightConfig->SightRadius = 900.0f;
    SightConfig->LoseSightRadius = 1100.0f;
    SightConfig->PeripheralVisionAngleDegrees = 40.0f;

    SightConfig->DetectionByAffiliation.bDetectEnemies = false;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = false;

    AIPerceptionComponent->ConfigureSense(*SightConfig);
    
   /* AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAgentController::HandlePerceptionUpdated);*/
}

void AAgentController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

    if (BTAsset)
    {
        RunBehaviorTree(BTAsset);
    }
}

void AAgentController::HandlePerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    if (UBlackboardComponent* MyBlackboard = GetBlackboardComponent())
    {
        
        if (Stimulus.WasSuccessfullySensed())
        {
            MyBlackboard->SetValueAsObject(PlayerKey, Actor);
        }
        else
        {
            MyBlackboard->ClearValue(PlayerKey);
        }
    }
}
