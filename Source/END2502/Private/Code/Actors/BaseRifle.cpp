// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/BaseRifle.h"
#include "Components/SkeletalMeshComponent.h"
#include "../END2502.h"
#include "Code/Actors/BasePlayer.h"


// Sets default values
ABaseRifle::ABaseRifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SetRootComponent(SkeletalMesh);

	Pawn = nullptr;
	ActionHappening = false;
	ResetTimer = 2.0f;
	Alive = true;
}

FVector ABaseRifle::GetSource() const
{
	return SkeletalMesh->GetSocketLocation("MuzzleFlashSocket");
}

float ABaseRifle::GetCurrentAmmo() const
{
	return CurrentAmmo;
}

FRotator ABaseRifle::GetBaseAimRotation() const
{

	if (!BasePlayer || !BasePlayer->PlayerHUDInstance)
	{
		UE_LOG(Game, Error, TEXT("BasePlayer or PlayerHUDInstance is nullptr in GetBaseAimRotation"));
		return Pawn->GetBaseAimRotation();
	}
	
	FVector Location = GetSource();

	FVector Destination = BasePlayer->PlayerHUDInstance->GetDestination();

	FVector Direction = Destination - Location;
	
	if (Direction.IsZero())
	{
		return Pawn->GetBaseAimRotation();
		UE_LOG(Game, Error, TEXT("Direction Is Zero in GetBaseAimRotation"));
	}
	
	if (Pawn == BasePlayer)
	{
		UE_LOG(Game, Warning, TEXT("Pawn is BasePlayer, using FRotationMatrix::MakeFromX(Direction).Rotator()"));
		return FRotationMatrix::MakeFromX(Direction).Rotator();
	}
	else
	{
		UE_LOG(Game, Warning, TEXT("Pawn is not BasePlayer, using Pawn->GetBaseAimRotation()"));
		return Pawn->GetBaseAimRotation();
	}
}

// Called when the game starts or when spawned
void ABaseRifle::BeginPlay()
{
	Super::BeginPlay();
	


	AActor* Actor = GetParentActor();

	//Down Cast
	Pawn = Cast<APawn>(Actor);

	if (Pawn)
	{
		//Vaild, 
		UE_LOG(Game, Warning, TEXT("BaseRifle Actor is %s"), *Pawn->GetName());

		
	}
	else
	{
		//Not Vaild
		UE_LOG(Game, Log, TEXT("Number are %d or %f"), 4, 7.3f);
	}

	UE_LOG(Game, Error, TEXT("Velocity is %s"), *GetVelocity().ToString());

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	ACharacter* PlayerCharacter = PC ? Cast<ACharacter>(PC->GetPawn()) : nullptr;

	if (PlayerCharacter)
	{
		UE_LOG(Game, Warning, TEXT("Player Character is %s"), *PlayerCharacter->GetName());
		BasePlayer = Cast<ABasePlayer>(PlayerCharacter);

		if (BasePlayer)
		{
			UE_LOG(Game, Warning, TEXT("Player Character is %s"), *BasePlayer->GetName());
		}
		else
		{
			UE_LOG(Game, Error, TEXT("Player Character is not of type ABasePlayer"));
		}
	}
	else
	{
		UE_LOG(Game, Error, TEXT("Player Character is nullptr"));
	}

	ReloadAmmo();
}


void ABaseRifle::Attack()
{
	if (CanShoot()) 
	{
		ActionHappening = true;

		FVector Location = GetSource();
		FRotator Rotation = GetBaseAimRotation();
		FActorSpawnParameters Params;
		Params.Owner = Pawn;
		Params.Instigator = Pawn->GetInstigator();
		GetWorld()->SpawnActor<AActor>(ProjectileClass, Location, Rotation, Params);

		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ABaseRifle::ActionStopped, ResetTimer);

		OnRifleAttack.Broadcast(Pawn);

		UseAmmo();
	}

}

void ABaseRifle::RequestReload()
{
	if (!ActionHappening)
	{
		ActionHappening = true;
		OnReloadStart.Broadcast(Pawn);
	}
}


void ABaseRifle::ActionStopped()
{
	ActionHappening = false;
	OnActionStopped.Broadcast(Pawn);
}

void ABaseRifle::ReloadAmmo()
{
	CurrentAmmo = MaxAmmo;
	OnAmmoChanged.Broadcast(CurrentAmmo, MaxAmmo);
}

void ABaseRifle::OwnerDied()
{
	Alive = false;
}

void ABaseRifle::UseAmmo()
{
	CurrentAmmo = FMath::Max(CurrentAmmo - 1.0f, 0.0f);
	OnAmmoChanged.Broadcast(CurrentAmmo, MaxAmmo);
	
}

bool ABaseRifle::CanShoot() const
{
	
	return !ActionHappening && Alive && CurrentAmmo > 0;
}

// Called every frame
void ABaseRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

