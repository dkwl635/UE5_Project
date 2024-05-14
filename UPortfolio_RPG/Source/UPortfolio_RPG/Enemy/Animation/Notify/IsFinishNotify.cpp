// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Animation/Notify/IsFinishNotify.h"
#include "Enemy/Animation/EnemyAnimInstance.h"

void UIsFinishNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    UEnemyAnimInstance* Anim = Cast<UEnemyAnimInstance>(MeshComp->GetAnimInstance());
    if (Anim)
    {
        Anim->SetFinishAnim();
    }
}
