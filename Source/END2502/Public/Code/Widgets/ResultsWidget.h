// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ResultsWidget.generated.h"

/**
 * 
 */
UCLASS()
class END2502_API UResultsWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void SetWin();

	UFUNCTION()
	void LoadMainMenu();

protected:

	virtual void NativeConstruct() override;

	



	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButtonWithText* MenuButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButtonWithText* RestartButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UVerticalBox* ButtonArea;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UWidgetSwitcher* ResultsSwitch;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
	float TimeToMenu = 2.0f;

	
	
};
