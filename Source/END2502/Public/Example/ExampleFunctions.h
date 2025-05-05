// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExampleFunctions.generated.h"

UCLASS()
class END2502_API AExampleFunctions : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExampleFunctions();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//This Lets you call the function from Blueprints
	UFUNCTION(BlueprintCallable)
	void BlueprintCallable();

	//BlueprintImplementableEvent - Declares in C++, Define in Blueprint
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void BlueprintImplementableEvent();

	//BlueprintNativeEvent - Declares in C++, Define in C++ but with _Implementation
	//can Override in Blueprint
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void BlueprintNativeEvent(); // In C++ call using this 
	virtual void BlueprintNativeEvent_Implementation(); // in c++ override using this
	// all three lines

	UFUNCTION(BlueprintCallable)
	float PureFunction() const;

	//Multi Return Values
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	bool MultiReturnValues(AActor* Actor1, FRotator Rotation, AActor *& Actor2, int32 &Index);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
