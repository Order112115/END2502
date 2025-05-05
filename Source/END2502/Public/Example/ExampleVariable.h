// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExampleVariable.generated.h"

//create a type of delegate, letting us know the required function signature
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDelegateType, AActor*, OtherActor);

UCLASS(Abstract)
class END2502_API AExampleVariable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExampleVariable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool CPLusCPlus;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Variables|ReadOnly")
	bool VisibleAnywhere;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Variables|ReadOnly")
	uint8 VisibleDefaultsOnly;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Variables|ReadOnly")
	int32 VisibleInstanceOnly;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables|ReadWrite")

	float EditAnywhere;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables|ReadWrite")

	FName EditDefaultsOnlyOdd;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Variables|ReadWrite")

	FString EditInstanceOnlyOdd;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables|ReadWrite")

	FText EditDefaultsOnly;

	// Class Reference
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Variables|ClassRef")
	TSubclassOf<AActor> ClassType;

	//Create a variable of the delegate / Evernt Dispatcher
	/*UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = Delegate)
	FDelegateType OnDelegateInstance;*/

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Variables|ClassRef")
	TArray<int32> ValueArry;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Variables|ClassRef")
	TArray<UObject *> PointerArry;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void ExampleBoundFunction(AActor* Actor);

	UFUNCTION()
	void AnotherBoundFunction(AActor* Actor);
};
