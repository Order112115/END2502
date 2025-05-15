// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/BaseDamagePickup.h"
#include "Particles/ParticleSystemComponent.h"
#include "Code/Actors/BasePickup.h"
#include "Components/BoxComponent.h"
#include "Engine/DamageEvents.h"

ABaseDamagePickup::ABaseDamagePickup()
{
	
	ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));
    ParticleSystemComponent->SetupAttachment(BoxComponent);
	ParticleSystemComponent->SetRelativeLocation(FVector(0.f, 0.f, -30.f));
	ParticleSystemComponent->SetRelativeScale3D(FVector(0.4f, 0.4, 0.25));
}

void ABaseDamagePickup::HandlePickup(AActor* OtherActor, const FHitResult& SweepResult)
{
	Super::HandlePickup(OtherActor, SweepResult);

	AController* ActorController = OtherActor->GetInstigatorController();

	TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
	FDamageEvent DamageEvent(ValidDamageTypeClass);

	OtherActor->TakeDamage(Damage, DamageEvent, ActorController, this);
}

void ABaseDamagePickup::PostPickup()
{
}
