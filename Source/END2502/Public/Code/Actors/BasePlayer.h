// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Code/Actors/BaseCharactor.h"
#include "Both/CharacterAnimation.h"
#include "BasePlayer.generated.h"




/**
 * 
 */
UCLASS()
class END2502_API ABasePlayer : public ABaseCharactor
{
	GENERATED_BODY()
public:
	ABasePlayer();

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Variables|ClassRef")
	TSubclassOf<AActor> WeaponClass;

	UPROPERTY()
	class UPlayerHUD* PlayerHUDInstance;

	

protected:
	virtual void BeginPlay() override;

	virtual void HandleHurt(float Ratio) override;

	virtual void HandleDeathStart(float Ratio) override;

	class USpringArmComponent* SpringArm;
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	TSubclassOf<UUserWidget> HUDClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	APlayerController* PlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	UUserWidget* HUDObject;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Attack();

	void Reload();

	
private:
	
	void InputAxisMoveForward(float AxisValue);
	void InputAxisStrafe(float AxisValue);
};
