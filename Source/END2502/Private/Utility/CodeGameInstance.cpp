// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/CodeGameInstance.h"
#include <Kismet/KismetSystemLibrary.h>
#include "Engine/Engine.h"
#include "../END2502.h"

void UCodeGameInstance::LoadFristLevel()
{
	LoadLevelSafe(FirstLevelIndex);
}

void UCodeGameInstance::QuitTheGame()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}

void UCodeGameInstance::LoadCurrentLevel()
{
	LoadLevelSafe(CurrentLevelIndex);
}

void UCodeGameInstance::LoadMainMenu()
{
	LoadLevelSafe(0);
}

void UCodeGameInstance::LoadLevelSafe(int32 LevelIndex)
{
    if (GameLevel.IsValidIndex(LevelIndex))
    {
		CurrentLevelIndex = LevelIndex;

        UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull);
        if (World == nullptr)
        {
            UE_LOG(LogTemp, Warning, TEXT("Invalid WorldContextObject."));
            return;
        }

        const bool bAbsolute = true;
        const ETravelType TravelType = (bAbsolute ? TRAVEL_Absolute : TRAVEL_Relative);
        FWorldContext& CurrentWorldContext = GEngine->GetWorldContextFromWorldChecked(World);
        FString Cmd = GameLevel[LevelIndex].ToString();

        FURL TestURL(&CurrentWorldContext.LastURL, *Cmd, TravelType);
        if (TestURL.IsLocalInternal())
        {
            if (!GEngine->MakeSureMapNameIsValid(TestURL.Map))
            {
                UE_LOG(LogLevel, Warning, TEXT("WARNING: The map '%s' does not exist."), *TestURL.Map);
                return;
            }
        }

        GEngine->SetClientTravel(World, *Cmd, TravelType);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid Level Index: %d"), LevelIndex);
    }
}


