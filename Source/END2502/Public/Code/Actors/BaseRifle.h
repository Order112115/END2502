// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseRifle.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateType, AActor*, OtherActor);

UCLASS()
class END2502_API ABaseRifle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseRifle();

	void Attack();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Delegate)

	FDelegateType OnRifleAttack;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Delegate)

	FDelegateType OnActionStopped;

	UFUNCTION(BlueprintCallable)
	FVector GetSource() const;

	UFUNCTION(BlueprintCallable)
	FRotator GetBaseAimRotation() const;

	UFUNCTION(BlueprintCallable)
	void OwnerDied();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)

	class USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
	FName MuzzleFlashSocketName;

	UFUNCTION(BlueprintCallable)
	void ActionStopped();

	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")

	float ResetTimer;
private:
	
	UPROPERTY(EditAnywhere, Category = "Default")

	bool ActionHappening;

	UFUNCTION(BlueprintCallable)
	bool CanShoot() const;


	APawn* Pawn;

	UPROPERTY(EditAnywhere, Category = "Default")
	bool Alive;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class ABasePlayer* BasePlayer;


};
