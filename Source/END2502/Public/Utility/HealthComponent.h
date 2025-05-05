// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateTypeHealth, float, Ratio);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class END2502_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)

	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)

	float CurrentHealth;

private:
	UFUNCTION()
	void HandleDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Delegate)

	FDelegateTypeHealth OnHurt;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Delegate)

	FDelegateTypeHealth OnDeath;
		
};
