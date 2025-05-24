// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/CodeGameMode.h"
#include "Code/Actors/BaseCharactor.h"
#include "Code/Actors/BasePlayer.h"
#include "EngineUtils.h"
#include "Code/Actors/Spawner.h"
#include "../END2502.h"


void ACodeGameMode::RemoveEnemy(AActor* DestroyedActor)
{
	NumberOfEnemies--;

	if (NumberOfEnemies > 0)
	{

	}
    else
    {
        UE_LOG(Game, Error, TEXT("You Win"));
	
		if (ResultsWidgetObject)
		{
			ResultsWidgetObject->AddToViewport();
            ResultsWidgetObject->SetWin();
			CurrentPlayer->PlayerWin();

		}
		else
		{
			UE_LOG(Game, Error, TEXT("Error: Results Widget is not valid"));
		}
    }
	
}

void ACodeGameMode::AddEnemy(AActor* EnemyActor)
{
	EnemyActor->OnDestroyed.AddDynamic(this, &ACodeGameMode::RemoveEnemy);
	NumberOfEnemies++;

}

void ACodeGameMode::RemovePlayer()
{
    UE_LOG(Game, Error, TEXT("You Lose"));
    if (ResultsWidgetObject) {
		ResultsWidgetObject->AddToViewport();
        APlayerController* PlayerController = ResultsWidgetObject->GetOwningPlayer();

        if (PlayerController != nullptr)
        {
            FInputModeUIOnly InputMode;
            InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);

            if (ResultsWidgetObject != nullptr)
            {
                InputMode.SetWidgetToFocus(ResultsWidgetObject->TakeWidget());
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
        UE_LOG(Game, Error, TEXT("Error: Results Widget is not valid"));
    }
}

void ACodeGameMode::BeginPlay()
{
    Super::BeginPlay();

    UWorld* World = GetWorld();
    if (!World) return;

    
    for (TActorIterator<ABaseCharactor> It(World); It; ++It)
    {
        ABaseCharactor* BaseChar = *It;
        if (!BaseChar) continue;

        ABasePlayer* Player = Cast<ABasePlayer>(BaseChar);
        if (Player)
        {
            CurrentPlayer = Player;
            

            // Bind delegate to handle player lost event
			Player->OnPlayerLost.AddDynamic(this, &ACodeGameMode::RemovePlayer);

        }
        else
        {
            AddEnemy(BaseChar);
        }
    }

    // Add all MassSpawners as enemies
    for (TActorIterator<ASpawner> It(World); It; ++It)
    {
        ASpawner* Spawner = *It;
        if (Spawner)
        {
            AddEnemy(Spawner);
        }
    }

    // UI: Create and store Results Widget
    APlayerController* PC = World->GetFirstPlayerController();
    if (PC && ResultsWidgetClass)
    {
        UUserWidget* Widget = CreateWidget<UUserWidget>(PC, ResultsWidgetClass);
        ResultsWidgetObject = Cast<UResultsWidget>(Widget);
    }

}
