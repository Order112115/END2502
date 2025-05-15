// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Actors/BasePickup.h"
#include "BaseDamagePickup.generated.h"

/**
 * 
 */
UCLASS()
class END2502_API ABaseDamagePickup : public ABasePickup
{
	GENERATED_BODY()
public:
	ABaseDamagePickup();
protected:

	virtual void HandlePickup(AActor* OtherActor, const FHitResult& SweepResult) override;
	virtual void PostPickup() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UParticleSystemComponent* ParticleSystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)

	float Damage;

private:

};
