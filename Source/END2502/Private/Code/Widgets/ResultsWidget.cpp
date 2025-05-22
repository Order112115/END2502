// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Widgets/ResultsWidget.h"
#include "Utility/CodeGameInstance.h"
#include "Both/ButtonWithText.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/VerticalBox.h"

void UResultsWidget::NativeConstruct()
{
	UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull);
	if (UCodeGameInstance* GameInstance = Cast<UCodeGameInstance>(World->GetGameInstance()))
	{
		if (MenuButton)
		{
			MenuButton->OnClickedEvent.AddDynamic(GameInstance, &UCodeGameInstance::LoadMainMenu);
		}
		if (RestartButton)
		{
			RestartButton->OnClickedEvent.AddDynamic(GameInstance, &UCodeGameInstance::LoadCurrentLevel);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Error: We Need Code version of GameInstance"));
	}
}

void UResultsWidget::SetWin()
{
	ButtonArea->SetVisibility(ESlateVisibility::Hidden);
	ResultsSwitch->SetActiveWidgetIndex(1);
    FTimerHandle TimerHandle;

    GetWorld()->GetTimerManager().SetTimer(
        TimerHandle,
        this,
        &UResultsWidget::LoadMainMenu,
        TimeToMenu,    
        false     
    );
}

void UResultsWidget::LoadMainMenu()
{
	MenuButton->OnClickedEvent.Broadcast();
}

