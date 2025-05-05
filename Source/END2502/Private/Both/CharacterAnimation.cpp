// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/CharacterAnimation.h"
#include "KismetAnimationLibrary.h"

void UCharacterAnimation::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Pawn = TryGetPawnOwner();


	if (Pawn)
	{
		//is Valid
		Velocity = Pawn->GetVelocity().Size();

		Direction = UKismetAnimationLibrary::CalculateDirection(Pawn->GetVelocity(), Pawn->GetActorRotation());

	}
	else {
		//Not Valid
		
	}
	PreviewWindowUpdate();


}

void UCharacterAnimation::FireAnimation()
{
	PlaySlotAnimationAsDynamicMontage(FireAsset, ActionSlotName);
}

void UCharacterAnimation::HitAnimation(float NotUsed)
{
	PlaySlotAnimationAsDynamicMontage(HitAsset, ActionSlotName);

}

//void UCharacterAnimation::DeathAnimation()
//{
//	
//}
//
void UCharacterAnimation::DeathAnimation_Implementation()
{
	if (DeathAsset.Num() > 0)
	{
		int32 RandomIndex = FMath::RandRange(0, DeathAsset.Num() - 1);
		CurrentDeathAsset = DeathAsset[RandomIndex];
	}
}

void UCharacterAnimation::PreviewWindowUpdate_Implementation()
{
	if(DebugHit)
	{
		DebugHit = false;
		HitAnimation(0.0f);
	}
	else
	{
		if (DebugDeath)
		{
			DebugDeath = false;
			DeathAnimation();
		}
	}
}
