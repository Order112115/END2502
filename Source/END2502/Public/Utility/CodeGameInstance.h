// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CodeGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class END2502_API UCodeGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:

protected:
	

	UFUNCTION()
	void LoadLevelSafe(int32 LevelIndex);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
	TArray<FName> GameLevel = { FName(TEXT("CodeMainMenu")), FName(TEXT("CodeTestingMap")) };;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
	int32 FirstLevelIndex = 1;

	
public:
	UFUNCTION()
	void LoadFristLevel();

	UFUNCTION()
	void QuitTheGame();
};
