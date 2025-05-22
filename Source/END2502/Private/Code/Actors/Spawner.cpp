// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/Spawner.h"
#include "Components/CapsuleComponent.h"
#include "Utility/HealthComponent.h"
#include "Code/Actors/BaseAgent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "../END2502.h"
#include "Code/Actors/CodeGameMode.h"


ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CapsuleCollision = CreateDefaultSubobject<UCapsuleComponent>("SphereCollision");
	SetRootComponent(CapsuleCollision);

	SpawnerMesh = CreateDefaultSubobject<UStaticMeshComponent>("SpawnerMesh");
	SpawnerMesh->SetupAttachment(GetRootComponent());

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");

	AgentClass = ASpawner::StaticClass();

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();


	if (HealthComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("HealthComponent is not nullptr in BeginPlay"));
		HealthComponent->OnDeath.AddDynamic(this, &ASpawner::HandleDestroy);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("HealthComponent is nullptr in BeginPlay"));
	}

	GetWorldTimerManager().SetTimer(
		SpawnTimerHandle, // FTimerHandle member variable
		this,
		&ASpawner::SpawnBaseAgent,
		Timer, // Delay in seconds
		true  // Single shot
	);

}

void ASpawner::HandleDestroy(float Ratio)
{
	Destroy();
}

void ASpawner::SpawnBaseAgent()
{
	UWorld* World = GetWorld();
	if (World)
	{
		FVector SpawnLocation = GetActorLocation();
		FRotator SpawnRotation = GetActorRotation();
		FActorSpawnParameters SpawnParams;
		if (AgentClass)
		{
			AActor* SpawnedAgent = World->SpawnActor<AActor>(AgentClass, SpawnLocation, SpawnRotation, SpawnParams);

			// Add to NumberOfEnemies in CodeGameMode
			AGameModeBase* GameMode = World->GetAuthGameMode();
			if (GameMode)
			{
				class ACodeGameMode* CodeGameMode = Cast<ACodeGameMode>(GameMode);
				if (CodeGameMode && SpawnedAgent)
				{
					CodeGameMode->AddEnemy(SpawnedAgent);
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("AgentClass is nullptr in ASpawner"));
		}
	}
}


