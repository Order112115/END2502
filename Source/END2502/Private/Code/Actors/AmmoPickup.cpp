// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/AmmoPickup.h"
#include "Code/Actors/BasePlayer.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Code/Actors/BaseRifle.h"
#include "Utility/PickupInterface.h"
#include "../END2502.h"

AAmmoPickup::AAmmoPickup()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetupAttachment(BoxComponent);

}

void AAmmoPickup::HandlePickup(AActor* OtherActor, const FHitResult& SweepResult)
{

	// Try to cast the overlapping actor to ABasePlayer
	ABasePlayer* Player = Cast<ABasePlayer>(OtherActor);
	if (Player)
	{
		// Get the rifle from the player
		ABaseRifle* PlayerRifle = Player->GetWeaponObject();

		if (PlayerRifle)
		{
			RifleObject = PlayerRifle;
			// Now you can use RifleObject to add ammo, etc.
			addMaxAmmo = RifleObject->MaxAmmo += 10;
			float currentAmmo = RifleObject->GetCurrentAmmo();
			RifleObject->OnAmmoChanged.Broadcast(currentAmmo, addMaxAmmo);
		}
	}

	


}

void AAmmoPickup::PostPickup()
{
	Super::PostPickup();
}

bool AAmmoPickup::CanPickup(AActor* OtherActor) const
{
	IPickupInterface* I3 = Cast<IPickupInterface>(OtherActor);
	if (I3)
	{

		return I3->CanPickupAmmo();

	}
	return false;
}
