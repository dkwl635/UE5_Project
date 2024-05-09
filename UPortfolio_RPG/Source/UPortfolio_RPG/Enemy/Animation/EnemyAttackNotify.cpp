// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Animation/EnemyAttackNotify.h"
#include "Enemy/Enemy.h"

void UEnemyAttackNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

    AEnemy* Enemy = Cast<AEnemy>(MeshComp->GetOwner());
    if (Enemy)
    {
        // 파티클을 실행하는 함수를 호출합니다.
        Enemy->PlayAttackParticle();
    }
}
