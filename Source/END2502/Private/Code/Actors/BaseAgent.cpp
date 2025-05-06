// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/BaseAgent.h"
#include "Components/SkeletalMeshComponent.h"
#include "../END2502.h"

ABaseAgent::ABaseAgent()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

void ABaseAgent::BeginPlay()
{
	Super::BeginPlay();

}

void ABaseAgent::PostLoad()
{
	Super::PostLoad();

	USkeletalMeshComponent* MeshComponent = GetMesh();
	if (MeshComponent)
	{
		int32 MaterialCount = MeshComponent->GetNumMaterials();

		for (int32 i = 0; i < MaterialCount; ++i)
		{
			UMaterialInstanceDynamic* MaterialInstance = MeshComponent->CreateAndSetMaterialInstanceDynamic(i);

			if (MaterialInstance)
			{
				MaterialInstance->SetVectorParameterValue(TintName, Color);
			}


		}
	}
}

void ABaseAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (WeaponObject)
	{
		WeaponObject->Attack();
	}
	else
	{
		UE_LOG(Game, Error, TEXT("WeaponObject is nullptr in Attack"));
	}*/
}

