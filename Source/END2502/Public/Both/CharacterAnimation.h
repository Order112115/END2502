// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimation.generated.h"

/**
 * 
 */
UCLASS()
class END2502_API UCharacterAnimation : public UAnimInstance
{
	GENERATED_BODY()
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UFUNCTION(BlueprintCallable)
	void FireAnimation();

	UFUNCTION(BlueprintCallable)
	void HitAnimation(float NotUsed);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DeathAnimation();
	virtual void DeathAnimation_Implementation();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default");
	float Velocity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Default");
	float Direction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
	bool DebugFire;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default");
	FName ActionSlotName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
	UAnimSequence* FireAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
	UAnimSequence* HitAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
	UAnimSequence* CurrentDeathAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
	TArray<UAnimSequence*> DeathAsset;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
	bool DebugHit;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Default")
	bool DebugDeath;

	UFUNCTION(BlueprintNativeEvent)
	void PreviewWindowUpdate();
	virtual void PreviewWindowUpdate_Implementation();
};
