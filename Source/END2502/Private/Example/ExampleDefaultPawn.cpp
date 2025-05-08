// Fill out your copyright notice in the Description page of Project Settings.


#include "Example/ExampleDefaultPawn.h"
/////////////ADDED////////////////
#include "../END2502.h"
#include "Example/ExampleActorWithInterfaces.h"
#include "EngineUtils.h"
//////////////////////////////////
#include "GameFramework/PlayerInput.h"

// Sets default values
AExampleDefaultPawn::AExampleDefaultPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AExampleDefaultPawn::BeginPlay()
{
	////////////////////////////////////END
	Super::BeginPlay();
	//Up Cast
	AActor* Actor = this;

	//Down Cast
	APawn* Pawn = Cast<APawn>(Actor);

	if (Pawn)
	{
		//Vaild, 
		UE_LOG(Game, Warning, TEXT("Actor is %s"), *Pawn->GetName());
	}
	else
	{
		//Not Vaild
		UE_LOG(Game, Log, TEXT("Number are %d or %f"), 4, 7.3f);
	}

	UE_LOG(Game, Error, TEXT("Velocity is %s"), *GetVelocity().ToString());
	UE_LOG(Game, Warning, TEXT("It is %s"), true? TEXT("TRUE") : TEXT("FALSE"));

	//////////////////////////////////// GAR

	for (TActorIterator<AExampleActorWithInterfaces> It(GetWorld()); It; ++It)
	{
		Actor = *It;
		//Cannot cast with UInterfaces
		UExampleInterface *U = Cast<UExampleInterface>(Actor);
		if (U)
		{
			//U->TestFunction();//Nothing Showing Up
			UE_LOG(Game, Log, TEXT("In the U cast"));
		}
		// This is the way to use an Unreal interface form C++
		IExampleInterface* I = Cast<IExampleInterface>(Actor);
		if (I)
		{
			I->TestFunction();
			UE_LOG(Game, Log, TEXT("In the I cast"));
			
		}
	}
} 

void AExampleDefaultPawn::Spawn()
{
	FActorSpawnParameters Params;
	Params.Instigator = this;
	GetWorld()->SpawnActor<AActor>(SpawnBlueprintClass, GetTransform(), Params);
}

// Called every frame
void AExampleDefaultPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AExampleDefaultPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//We do not need to move the project setting here
	UPlayerInput::AddEngineDefinedActionMapping(FInputActionKeyMapping("TEST_SPAWN", EKeys::SpaceBar));

	PlayerInputComponent->BindAction("TEST_SPAWN", EInputEvent::IE_Pressed, this, &AExampleDefaultPawn::Spawn);
}

