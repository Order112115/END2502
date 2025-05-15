// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/BasePlayer.h"
#include "Code/Actors/BaseRifle.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/ChildActorComponent.h"
#include "Both/CharacterAnimation.h"
#include "../END2502.h"
#include "Blueprint/UserWidget.h"
#include "Both/PlayerHUD.h"
#include "Utility/HealthComponent.h"

ABasePlayer::ABasePlayer()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetRelativeLocation(FVector(0.,80., 90.));
	SpringArm->SetupAttachment(GetRootComponent()/*, only need to use this if we are using sockets*/ );
	SpringArm->bUsePawnControlRotation = true;

	SpringArm->TargetArmLength = 205.f;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	
	
	WeaponClass = ABasePlayer::StaticClass();
	HUDClass = ABasePlayer::StaticClass();
}

bool ABasePlayer::CanPickupHealth() const
{
	return true;
}

void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
	AActor* Actor = GetController();
	PlayerController = Cast<APlayerController>(Actor);
	if (PlayerController)
	{
		UUserWidget* PlayerHUDWidget = CreateWidget<UUserWidget>(PlayerController, HUDClass);
		if (PlayerHUDWidget)
		{
			PlayerHUDWidget->AddToViewport();
			HUDObject = PlayerHUDWidget;

			PlayerHUDInstance = Cast<UPlayerHUD>(PlayerHUDWidget);

			WeaponObject->OnAmmoChanged.AddDynamic(PlayerHUDInstance, &UPlayerHUD::SetAmmo);

			WeaponObject->ReloadAmmo();

			HealthComponent->OnHeal.AddDynamic(PlayerHUDInstance, &UPlayerHUD::SetHealth);
		}
		else
		{
			UE_LOG(Game, Error, TEXT("Failed to create widget"));
		}
	}
	else
	{
		UE_LOG(Game, Error, TEXT("PlayerController is nullptr in BeginPlay"));
		Destroy();
	}

}

void ABasePlayer::HandleHurt(float Ratio)
{
	Super::HandleHurt(Ratio);

	if (HUDObject)
	{
		UPlayerHUD* PlayerHUD = Cast<UPlayerHUD>(HUDObject);
		if (PlayerHUD)
		{
			PlayerHUD->SetHealth(Ratio);
			
		}
		else
		{
			UE_LOG(Game, Error, TEXT("HUDObject is not of type UPlayerHUD in HandleHurt"));
		}
	}
	else
	{
		UE_LOG(Game, Error, TEXT("HUDObject is nullptr in HandleHurt"));
	}
}

void ABasePlayer::HandleDeathStart(float Ratio)
{
	Super::HandleDeathStart(Ratio);

	if (HUDObject)
	{
		UPlayerHUD* PlayerHUD = Cast<UPlayerHUD>(HUDObject);
		if (PlayerHUD)
		{
			PlayerHUD->SetHealth(Ratio);

		}
		else
		{
			UE_LOG(Game, Error, TEXT("HUDObject is not of type UPlayerHUD in HandleDeathStart"));
		}

		if (PlayerController)
		{
			DisableInput(PlayerController);
			
		}

		if (!PlayerController)
		{
			UE_LOG(Game, Error, TEXT("PlayerController is nullptr in DisablePlayerInput"));
		}
	}
	else
	{
		UE_LOG(Game, Error, TEXT("HUDObject is nullptr in HandleDeathStart"));
	}
}

void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Camera Movement
	PlayerInputComponent->BindAxis("TurnRight", this, &ABasePlayer::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ABasePlayer::AddControllerPitchInput);

	//PlayerMovement
	PlayerInputComponent->BindAxis("MoveForward", this, &ABasePlayer::InputAxisMoveForward);
	PlayerInputComponent->BindAxis("Strafe", this, &ABasePlayer::InputAxisStrafe);
	PlayerInputComponent->BindAction("AttackInput", EInputEvent::IE_Pressed, this, &ABasePlayer::Attack);
	PlayerInputComponent->BindAction("Reload", EInputEvent::IE_Pressed, this, &ABasePlayer::Reload);
}

void ABasePlayer::Attack()
{
	if (WeaponObject)
	{
		WeaponObject->Attack();
	}
	else
	{
		UE_LOG(Game, Error, TEXT("WeaponObject is nullptr in Attack"));
	}

}

void ABasePlayer::Reload()
{
	if (WeaponObject)
	{
		WeaponObject->RequestReload();
	}
}

void ABasePlayer::InputAxisMoveForward(float AxisValue)
{
	/* 
	FRotator Break = GetControlRotation();
	FRotator Make(0., Break.Yaw, 0.);
	FVector WorldDirection = Make.Vector();
	AddMovementInput(WorldDirection, AxisValue);

	This is the same as AddMovementInput(FRotator(0., GetControlRotation().Yaw, 0.).Vector(), AxisValue);
	*/

	AddMovementInput(FRotator(0., GetControlRotation().Yaw, 0.).Vector(), AxisValue);


}

void ABasePlayer::InputAxisStrafe(float AxisValue)
{
	FRotator Break = GetControlRotation();
	FRotator Make(0., Break.Yaw, 0.);
	FVector WorldDirection = FRotationMatrix(Make).GetScaledAxis(EAxis::Y);
	AddMovementInput(WorldDirection, AxisValue);
}