// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/BasePickup.h"
#include "Components/BoxComponent.h"
// Sets default values
ABasePickup::ABasePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;



	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(GetRootComponent());

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABasePickup::BoundOverlap);



}

// Called when the game starts or when spawned
void ABasePickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABasePickup::BoundOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (CanPickup(OtherActor))
	{
		HandlePickup(OtherActor, SweepResult);
		PostPickup();
	}
	
}


void ABasePickup::HandlePickup(AActor* OtherActor, const FHitResult& SweepResult)
{

}

void ABasePickup::PostPickup()
{
	Destroy();
}

bool ABasePickup::CanPickup(AActor* OtherActor) const
{
	return true;
}
