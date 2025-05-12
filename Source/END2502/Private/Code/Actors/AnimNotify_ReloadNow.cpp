// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/AnimNotify_ReloadNow.h"
#include "Both/CharacterAnimation.h"

UAnimNotify_ReloadNow::UAnimNotify_ReloadNow()
{
}

FString UAnimNotify_ReloadNow::GetNotifyName_Implementation() const
{
	return TEXT("Reload Now");
}

void UAnimNotify_ReloadNow::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{

}

void UAnimNotify_ReloadNow::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    if (MeshComp)
    {
        UCharacterAnimation* AnimInstance = Cast<UCharacterAnimation>(MeshComp->GetAnimInstance());
        if (AnimInstance)
        {
            AActor* Owner = MeshComp->GetOwner();
            AnimInstance->OnReloadNow.Broadcast(Owner);
        }
    }
}

void UAnimNotify_ReloadNow::ValidateAssociatedAssets()
{
}
