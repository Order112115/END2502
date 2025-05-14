// Fill out your copyright notice in the Description page of Project Settings.


#include "Example/ExampleActorWithInterfaces.h"
#include "../END2502.h"
// Sets default values
AExampleActorWithInterfaces::AExampleActorWithInterfaces()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AExampleActorWithInterfaces::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExampleActorWithInterfaces::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExampleActorWithInterfaces::TestFunction()
{
	UE_LOG(Game, Log, TEXT("IN C++ AExampleActorWithInterfaces::TestFunction"));
}

void AExampleActorWithInterfaces::BlueprintNativeEvent_Implementation()
{
	IExampleInterfaceThree::BlueprintNativeEvent_Implementation(); // Call the parent implementation
	UE_LOG(Game, Log, TEXT("IN C++ AExampleActorWithInterfaces::BlueprintNativeEvent_Implementation (Parent)"));
}

