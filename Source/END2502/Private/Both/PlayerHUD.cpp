// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/PlayerHUD.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Blueprint/SlateBlueprintLibrary.h"

void UPlayerHUD::NativeConstruct()
{
	Super::NativeConstruct();

	CrosshairDynamicMaterial = Crosshair->GetDynamicMaterial();
	EndPoint = FVector::ZeroVector;
	ColorName = FName("Color");
	SafeColor = FLinearColor(0.1f, .7f, .7f, 1.0f);
	DangerColor = FLinearColor(.85f, 0.1f, 0.1f, 1.0f);
	
}

FVector UPlayerHUD::GetDestination() const
{

	UE_LOG(LogTemp, Error, TEXT("GetDestination called. EndPoint: %s"), *EndPoint.ToString());
	return EndPoint;
}


void UPlayerHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	PerformLineTrace();

}


void UPlayerHUD::PerformLineTrace()
{
	APlayerController* Player = GetOwningPlayer();

	FVector2D PixelPosition, ViewportPosition;
	FVector2D LocalCoordinate(0.0f, 0.0f);
	FGeometry LGeometry = Crosshair->GetCachedGeometry();
	USlateBlueprintLibrary::LocalToViewport(GetWorld(), LGeometry, LocalCoordinate, PixelPosition, ViewportPosition);

	FVector2D AbsoluteSize = LGeometry.GetAbsoluteSize();
	AbsoluteSize *= 0.5f;
	FVector2D ScreenPosition = PixelPosition + AbsoluteSize;

	FVector WorldPosition, WorldDirection;
	if (Player->DeprojectScreenPositionToWorld(ScreenPosition.X, ScreenPosition.Y, WorldPosition, WorldDirection))
	{
		FVector Start = WorldPosition;
		FVector End = WorldPosition + (WorldDirection * 100000.0f);
		EndPoint = End;
		FHitResult OutHit;

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(Player->GetPawn());

		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
		


		if (GetWorld()->LineTraceSingleByObjectType(OutHit, Start, End, FCollisionObjectQueryParams(ObjectTypes), Params))
		{
			EndPoint = OutHit.ImpactPoint;

			if (OutHit.GetActor())
			{
				if (OutHit.GetComponent()->GetCollisionObjectType() == ECC_WorldDynamic)
				{
					// If the hit object is the floor, set the crosshair to SafeColor
					if (CrosshairDynamicMaterial)
					{
						CrosshairDynamicMaterial->SetVectorParameterValue(ColorName, SafeColor);
					}
				}
				else
				{
					// If the hit object is not the floor, set the crosshair to DangerColor
					if (CrosshairDynamicMaterial)
					{
						CrosshairDynamicMaterial->SetVectorParameterValue(ColorName, DangerColor);
					}
				}
			}
		}
		else
		{
			if (CrosshairDynamicMaterial)
			{
				CrosshairDynamicMaterial->SetVectorParameterValue(ColorName, SafeColor);
			}
		}
		
		//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.0f, 0, 1.0f);
		//DrawDebugSphere(GetWorld(), EndPoint, 25.0f, 12, FColor::Red, false, 1.0f);
	}
}



void UPlayerHUD::SetHealth(float Percent)
{
    
        HealthBar->SetPercent(Percent);
    
}
