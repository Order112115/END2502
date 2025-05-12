// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <Both/CharacterAnimation.h>

#include "BaseRifle.h"
#include "BaseCharactor.generated.h"


UCLASS()
class END2502_API ABaseCharactor : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharactor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")

	ABaseRifle* WeaponObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")

	UCharacterAnimation* AnimationBP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UChildActorComponent* ChildActor;
 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default")

	TSubclassOf<AActor> PlayerWeaponClass;

	UFUNCTION()
	void OnRifleAttackHandler(AActor* OtherActor);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UHealthComponent* HealthComponent;


	UFUNCTION()
	virtual void HandleHurt(float Ratio);

	UFUNCTION()
	virtual void HandleDeathStart(float Ratio);

	UFUNCTION()
	void ActionStopped(AActor* OtherActor);

	UFUNCTION()
	void ReloadAmmo(AActor* OtherActor);

	UFUNCTION()
	void ReloadAnimation(AActor* OtherActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
