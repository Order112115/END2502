// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/BaseCharactor.h"
#include "Utility/HealthComponent.h"
#include "../END2502.h"
#include <Code/Actors/BasePlayer.h>
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Code/Actors/UAnimNotify_ReloadEnded.h"
// Sets default values
ABaseCharactor::ABaseCharactor()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	GetMesh()->SetRelativeLocation(FVector(0.0, 0.0, -90.0));
	GetMesh()->SetRelativeRotation(FRotator(0.0, 270.0, 0.0));

	ChildActor = CreateDefaultSubobject<UChildActorComponent>("ChildActor");
	ChildActor->SetupAttachment(GetMesh(), "PlaceWeaponHere");

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");

	

	ABasePlayer* BasePlayer = Cast<ABasePlayer>(GetOwner());
	if (BasePlayer)
	{
		PlayerWeaponClass = BasePlayer->WeaponClass;
	}
}

// Called when the game starts or when spawned
void ABaseCharactor::BeginPlay()
{
	Super::BeginPlay();

	ChildActor->SetChildActorClass(PlayerWeaponClass);
	WeaponObject = Cast<ABaseRifle>(ChildActor->GetChildActor());
	AnimationBP = Cast<UCharacterAnimation>(GetMesh()->GetAnimInstance());
	
	if (!WeaponObject)
	{
		UE_LOG(Game, Error, TEXT("WeaponObject is nullptr after casting"));
	}
	if (!AnimationBP)
	{
		UE_LOG(Game, Error, TEXT("AnimationBP is nullptr after casting"));
	}
	if (WeaponObject)
	{
		WeaponObject->OnRifleAttack.AddDynamic(this, &ABaseCharactor::OnRifleAttackHandler);
	}
	if (HealthComponent)
	{
		HealthComponent->OnHurt.AddDynamic(this, &ABaseCharactor::HandleHurt);
		HealthComponent->OnDeath.AddDynamic(this, &ABaseCharactor::HandleDeathStart);
	}
	else
	{
		UE_LOG(Game, Error, TEXT("HealthComponent is nullptr in ABaseCharactor::BeginPlay"));
	}
	if (AnimationBP) {
		AnimationBP->OnReloadEnded.AddDynamic(this, &ABaseCharactor::ActionStopped);
		AnimationBP->OnReloadNow.AddDynamic(this, &ABaseCharactor::ReloadAmmo);
	}
	else
	{
		UE_LOG(Game, Error, TEXT("AnimationBP is nullptr in ABaseCharactor::BeginPlay"));
	}
	if (WeaponObject) {
		WeaponObject->OnReloadStart.AddDynamic(this, &ABaseCharactor::ReloadAnimation);
	}

}



void ABaseCharactor::OnRifleAttackHandler(AActor* OtherActor)
{
	if (AnimationBP)
	{
		AnimationBP->FireAnimation();
	}
	else
	{
		UE_LOG(Game, Error, TEXT("AnimationBP is nullptr in OnRifleAttackHandler"));
	}
}

void ABaseCharactor::HandleHurt(float Ratio)
{
	if (AnimationBP)
	{
		AnimationBP->HitAnimation(0.0f);
	}
	else
	{
		UE_LOG(Game, Error, TEXT("AnimationBP is nullptr in HandleHurt"));
	}
}

void ABaseCharactor::HandleDeathStart(float Ratio)
{

	if (AnimationBP)
	{
		AnimationBP->DeathAnimation_Implementation();
		SetActorEnableCollision(false);
		WeaponObject->OwnerDied();
	}
	else
	{
		UE_LOG(Game, Error, TEXT("AnimationBP is nullptr in HandleDeathStart"));
	}
}

void ABaseCharactor::ActionStopped(AActor* OtherActor)
{
	if (WeaponObject)
	{
		WeaponObject->ActionStopped();
	}
	else
	{
		UE_LOG(Game, Error, TEXT("WeaponObject is nullptr in ActionStopped"));
	}
}

void ABaseCharactor::ReloadAmmo(AActor* OtherActor)
{
	if (WeaponObject)
	{
		WeaponObject->ReloadAmmo();
	}
	else
	{
		UE_LOG(Game, Error, TEXT("WeaponObject is nullptr in ReloadAmmo"));
	}
}

void ABaseCharactor::ReloadAnimation(AActor* OtherActor)
{
	if (AnimationBP)
	{
		AnimationBP->ReloadAnimation();
	}
	else
	{
		UE_LOG(Game, Error, TEXT("AnimationBP is nullptr in ReloadAnimation"));
	}
}


// Called every frame
void ABaseCharactor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharactor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

