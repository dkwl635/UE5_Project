// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/DeathAnimNotify.h"
#include "Enemy/Enemy.h"
#include "Enemy/EnemyPool.h"
#include "Subsystem/ChaosDungeon/ChaosDungeonSubsystem.h"

void UDeathAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    AEnemy* Enemy = Cast<AEnemy>(MeshComp->GetOwner());
    if (Enemy)
    {
        UEnemyPool* Pool = Enemy->Pool;
        if(Pool)
        {
            Pool->Delete(Enemy);
        }
    }
}
