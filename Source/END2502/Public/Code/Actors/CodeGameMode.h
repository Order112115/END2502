// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include <Code/Widgets/ResultsWidget.h>
#include "CodeGameMode.generated.h"

/**
 * 
 */
UCLASS()
class END2502_API ACodeGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void RemoveEnemy(AActor* DestroyedActor);

	UFUNCTION()
	void AddEnemy(AActor* EnemyActor);

	UFUNCTION()
	void RemovePlayer();

protected: 
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
	float NumberOfEnemies;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
	class ABasePlayer* CurrentPlayer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
	class UResultsWidget* ResultsWidgetObject;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")
	class TSubclassOf<UResultsWidget> ResultsWidgetClass;
private:

};
