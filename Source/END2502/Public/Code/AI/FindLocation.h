// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FindLocation.generated.h"

UCLASS()
class END2502_API UFindLocation : public UBTTaskNode
{
	GENERATED_BODY()
	
	UFindLocation(); // Constructor declaration
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	UPROPERTY(EditAnywhere)
	float SearchRadius;

	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector LocationKey;
};
