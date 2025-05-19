// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Widgets/CodeMainMenu.h"
#include "Components/Button.h"
#include "Both/ButtonWithText.h"
#include "Utility/CodeGameInstance.h"

void UCodeMainMenu::NativeConstruct()
{
	UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull);
	if (UCodeGameInstance* GameInstance = Cast<UCodeGameInstance>(World->GetGameInstance()))
	{
		if (StartGameButton)
		{
			StartGameButton->OnClickedEvent.AddDynamic(GameInstance, &UCodeGameInstance::LoadFristLevel);
		}
		if (QuitGameButton)
		{
			QuitGameButton->OnClickedEvent.AddDynamic(GameInstance, &UCodeGameInstance::QuitTheGame);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to cast to UCodeGameInstance"));
	}
}
