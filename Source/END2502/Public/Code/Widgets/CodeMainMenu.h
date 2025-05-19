// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CodeMainMenu.generated.h"

/**
 * 
 */
UCLASS()
class END2502_API UCodeMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButtonWithText* StartGameButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButtonWithText* QuitGameButton;


public:

};
