// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Utility/EnemyInterface.h"

#include "Code/Actors/BaseCharactor.h"
#include "BaseAgent.generated.h"

/**
 * 
 */
UCLASS()
class END2502_API ABaseAgent : public ABaseCharactor, public IEnemyInterface
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	ABaseAgent();

	//----------------------------------------------------------------------//
	// IEnemyInterface
	//----------------------------------------------------------------------//
	virtual void EnemyAttack() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostLoad() override;

	virtual void Tick(float DeltaTime) override;

	virtual void HandleHurt(float Ratio) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	FName TintName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	FLinearColor Color;

	UFUNCTION()
	void HandleActionFinished(AActor* OtherActor);

	UFUNCTION()
	void UpdateBlackboardHealth(float Ratio);

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	FName ActionFInishedMessage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	FName HealthKey;
};
