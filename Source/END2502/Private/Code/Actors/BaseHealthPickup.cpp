// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/BaseHealthPickup.h"
#include "Utility/PickupInterface.h"

ABaseHealthPickup::ABaseHealthPickup()
{

}



void ABaseHealthPickup::PostPickup()
{
	Destroy();
}

bool ABaseHealthPickup::CanPickup(AActor* OtherActor) const
{
	IPickupInterface* I3 = Cast<IPickupInterface>(OtherActor);
	if (I3)
	{

		return I3->CanPickupHealth();

	}
	return false;
}
