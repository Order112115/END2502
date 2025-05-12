// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/UAnimNotify_ReloadEnded.h"
#include "Both/CharacterAnimation.h"

UUAnimNotify_ReloadEnded::UUAnimNotify_ReloadEnded()
{
}

FString UUAnimNotify_ReloadEnded::GetNotifyName_Implementation() const
{
    return TEXT("Reload Ended");
}

void UUAnimNotify_ReloadEnded::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
}

void UUAnimNotify_ReloadEnded::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    if (MeshComp)
    {
        UCharacterAnimation* AnimInstance = Cast<UCharacterAnimation>(MeshComp->GetAnimInstance());
        if (AnimInstance)
        {
            AActor* Owner = MeshComp->GetOwner();
            AnimInstance->OnReloadEnded.Broadcast(Owner);
        }
    }
}

void UUAnimNotify_ReloadEnded::ValidateAssociatedAssets()
{
}
