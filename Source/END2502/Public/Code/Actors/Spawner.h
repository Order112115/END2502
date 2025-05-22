// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class END2502_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)

	FTimerHandle SpawnTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* SpawnerMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UCapsuleComponent* CapsuleCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UHealthComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Timer = 10.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Variables|ClassRef")
	TSubclassOf<AActor> AgentClass;

	UFUNCTION()
	void HandleDestroy(float Ratio);
	
	UFUNCTION()
	void SpawnBaseAgent();

public:	
	
};
