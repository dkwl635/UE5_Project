// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/DeathAnimNotify.h"
#include "Enemy/Enemy.h"

void UDeathAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    AEnemy* Enemy = Cast<AEnemy>(MeshComp->GetOwner());
    if (Enemy)
    {
        Enemy->Destroy();
    }
}
