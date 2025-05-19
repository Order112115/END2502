// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/GamePlayerController.h"

void AGamePlayerController::BeginPlay()
{
	APlayerController* PlayerController = this;

	if (PlayerController != nullptr)
	{
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);

		const bool bFlushInput = false;
		if (bFlushInput)
		{
			PlayerController->FlushPressedKeys();
		}
	}
}
