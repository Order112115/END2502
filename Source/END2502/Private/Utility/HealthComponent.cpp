// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/HealthComponent.h"
#include "../END2502.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	MaxHealth = 5.0f;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	AActor* Owner = GetOwner();

	if (Owner)
	{
		// Bind the damage event
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::HandleDamage);
	}
	
}


void UHealthComponent::HandleDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f) return;

	
	CurrentHealth -= Damage;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("Actor %s took %f damage, current health: %f"), *DamagedActor->GetName(), Damage, CurrentHealth);

	float HealthRatio = CurrentHealth / MaxHealth;

	if (CurrentHealth > 0.0f)
	{
		OnHurt.Broadcast(HealthRatio);
	}
	else
	{
		AActor* Owner = GetOwner();

		Owner->OnTakeAnyDamage.RemoveDynamic(this, &UHealthComponent::HandleDamage);
		OnDeath.Broadcast(0.0f);
	}
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

