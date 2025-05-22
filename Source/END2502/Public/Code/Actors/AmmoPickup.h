// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Actors/BasePickup.h"
#include "AmmoPickup.generated.h"

/**
 * 
 */
UCLASS()
class END2502_API AAmmoPickup : public ABasePickup
{
	GENERATED_BODY()
	
public:
	AAmmoPickup();

protected:
	virtual void HandlePickup(AActor* OtherActor, const FHitResult& SweepResult) override;

	virtual void PostPickup() override;
	virtual bool CanPickup(AActor* OtherActor) const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)

	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)

	class ABaseRifle* RifleObject;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")

	TSubclassOf<AActor> PlayerWeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)

	class UPlayerHUD* HUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float addMaxAmmo = 10.0f;
};
