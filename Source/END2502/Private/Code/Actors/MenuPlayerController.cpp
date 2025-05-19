// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/MenuPlayerController.h"
#include "Blueprint/UserWidget.h"

AMenuPlayerController::AMenuPlayerController()
{
	MenuClass = AMenuPlayerController::StaticClass();
}

void AMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* MenuWidget = CreateWidget<UUserWidget>(this, MenuClass);
	if (MenuWidget)
	{
		MenuWidget->AddToViewport();
		APlayerController* PlayerController = this;

		if (PlayerController != nullptr)
		{
			FInputModeUIOnly InputMode;
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);

			if (MenuWidget != nullptr)
			{
				InputMode.SetWidgetToFocus(MenuWidget->TakeWidget());
			}
			PlayerController->SetInputMode(InputMode);

			const bool bFlushInput = false;
			if (bFlushInput)
			{
				PlayerController->FlushPressedKeys();
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create MenuWidget"));
	}
}


