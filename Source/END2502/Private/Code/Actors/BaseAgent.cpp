// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/BaseAgent.h"
#include "Components/SkeletalMeshComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h" 
#include "../END2502.h"
#include "BrainComponent.h"


ABaseAgent::ABaseAgent()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}



void ABaseAgent::BeginPlay()
{
	Super::BeginPlay();

	WeaponObject = Cast<ABaseRifle>(ChildActor->GetChildActor());
	if (WeaponObject)
	{
		WeaponObject->OnActionStopped.AddDynamic(this, &ABaseAgent::HandleActionFinished);

	}
	else
	{
		UE_LOG(Game, Error, TEXT("WeaponObject is nullptr in BeginPlay"));
	}

	UpdateBlackboardHealth(1.0f);

	WeaponObject->OnAmmoChanged.AddDynamic(this, &ABaseAgent::UpdateBlackboardAmmo);
	WeaponObject->ReloadAmmo();
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

	
}

void ABaseAgent::HandleHurt(float Ratio)
{
	UpdateBlackboardHealth(Ratio);
}

void ABaseAgent::HandleActionFinished(AActor* OtherActor)
{
	bool bSuccess = true;
	FAIMessage::Send(this, FAIMessage(ActionFInishedMessage, this, bSuccess));
}

void ABaseAgent::UpdateBlackboardHealth(float Ratio)
{
	AAIController* AICon = Cast<AAIController>(GetController());
	if (AICon)
	{
		UBlackboardComponent* BBComp = AICon->GetBlackboardComponent();
		if (BBComp)
		{
			BBComp->SetValueAsFloat(HealthKey, Ratio);
		}
	}
	else
	{
		UE_LOG(Game, Error, TEXT("AICon is nullptr in UpdateBLackboardHealth"));
	}
}

void ABaseAgent::UpdateBlackboardAmmo(float Current, float Max)
{
	AAIController* AICon = Cast<AAIController>(GetController());
	if (AICon)
	{
		UBlackboardComponent* BBComp = AICon->GetBlackboardComponent();
		if (BBComp)
		{
			BBComp->SetValueAsFloat(AmmoKey, Current);
		}
	}
	else
	{
		UE_LOG(Game, Error, TEXT("AICon is nullptr in UpdateBLackboardHealth"));
	}
}

void ABaseAgent::EnemyAttack()
{
	if (WeaponObject)
	{
		WeaponObject->Attack();
	}
	else
	{
		UE_LOG(Game, Error, TEXT("WeaponObject is nullptr in Attack"));
	}
}

void ABaseAgent::EnemyReload()
{
	if (WeaponObject)
	{
		WeaponObject->RequestReload();
	}
	else
	{
		UE_LOG(Game, Error, TEXT("WeaponObject is nullptr in Reload"));
	}
}

