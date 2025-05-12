// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class END2502_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()


protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* Crosshair;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)

	UMaterialInstanceDynamic* CrosshairDynamicMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)

	FLinearColor SafeColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor DangerColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	
	FName ColorName;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* CurrentAmmo;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* MaxAmmo;

	

	

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector EndPoint;

	UFUNCTION(BlueprintCallable)
	FVector GetDestination() const;

	void PerformLineTrace();

	UFUNCTION(BlueprintCallable)
	void SetAmmo(float Current, float Max);

	UFUNCTION(BlueprintCallable)
	void SetHealth(float Percent);
};
