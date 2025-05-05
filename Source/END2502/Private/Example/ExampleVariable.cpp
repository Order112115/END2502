// Fill out your copyright notice in the Description page of Project Settings.


#include "Example/ExampleVariable.h"
#include "../END2502.h"
// Sets default values
AExampleVariable::AExampleVariable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;// if you set bCanEverTick = false it does the same thing as this line

	ClassType = AExampleVariable::StaticClass();
	ValueArry.Add(3);
	ValueArry.Add(4);
	PointerArry.Add(this);
	PointerArry.Add(nullptr);
}

// Called when the game starts or when spawned
void AExampleVariable::BeginPlay()
{
	Super::BeginPlay();
	// This is how we bind to a delegate
	//Params sent into AddDynamic are teh same as the CreateEvent in the buleprint
	//As seen in Base Character Begin Play
	//OnDelegateInstance.AddDynamic(this, &AExampleVariable::ExampleBoundFunction);
	//OnDelegateInstance.AddDynamic(this, &AExampleVariable::AnotherBoundFunction);
	////this is how you call the delegate
	////as seen in rifle::attack
	//OnDelegateInstance.Broadcast(this);
}

// Called every frame
void AExampleVariable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AExampleVariable::ExampleBoundFunction(AActor* Actor)
{
	UE_LOG(Game, Error, TEXT("Function called by delegate"));
}

void AExampleVariable::AnotherBoundFunction(AActor* Actor)
{
	UE_LOG(Game, Warning, TEXT(" Another Function called by delegate"));
}

