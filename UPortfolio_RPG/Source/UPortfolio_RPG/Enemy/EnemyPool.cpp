// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyPool.h"
#include "AI/EnemyAIController.h"
#include "Enemy/Animation/EnemyAnimInstance.h"
#include "Subsystem/ChaosDungeon/ChaosDungeonSubsystem.h"

UEnemyPool::UEnemyPool()
{
    EnemyClass = AEnemy::StaticClass();
}

void UEnemyPool::Create(UWorld* World, uint32 Count)
{
    Pool.Reserve(Count);
    ActiveEnemies.Reserve(Count);
    CDSubsystem = World->GetSubsystem<UChaosDungeonSubsystem>();

    for (uint32 i = 0; i < Count; ++i)
    {
        AEnemy* NewEnemy = World->SpawnActor<AEnemy>(FVector::ZeroVector,FRotator::ZeroRotator);
        if (NewEnemy)
        {
            NewEnemy->SetActorHiddenInGame(true); // Render off
            NewEnemy->SetActorEnableCollision(false); // Collision off
            NewEnemy->SetActorTickEnabled(false); // Tick off
            NewEnemy->OwningController->UnPossess();
            
            //EnemyController->pause();
            Pool.Add(NewEnemy);
        }
    }
}

void UEnemyPool::Destroy()
{
    for (AEnemy* Enemy : Pool)
    {
        if (Enemy)
        {
            Enemy->Destroy();
            Enemy = nullptr;
        }
    }
    for (AEnemy* It : ActiveEnemies)
    {
        if (It)
        {
            It->Destroy();
            It = nullptr;
        }
    }
}

AEnemy* UEnemyPool::SpawnEnemy(const FTransform& InTransform, bool bEnableCollision, AActor* Owner, APawn* Instigator)
{
    AEnemy* Enemy = nullptr;

    if (Pool.Num() > 0)
    {
        Enemy = Pool.Pop(false);
        if(Enemy)
        {
            ActiveEnemies.Add(Enemy);
            Enemy->SetPool(this);
            Enemy->SetActorHiddenInGame(false);
            Enemy->SetActorEnableCollision(bEnableCollision);
            Enemy->SetActorTickEnabled(true);
            Enemy->PurificationScore = FMath::RandRange(100, 200);
            Enemy->SetActorTransform(InTransform);
            Enemy->IsDead = false;
            Enemy->OwningController->Possess(Enemy);

            UEnemyAnimInstance* AnimInstance = Enemy->GetAnimInstance();
            if (AnimInstance)
                AnimInstance->PlaySpawnMontage();
        }
    }
    return Enemy;
}
#include "BehaviorTree/BlackboardComponent.h"
void UEnemyPool::Delete(AEnemy* InEnemy)
{
    const int32 Index = ActiveEnemies.Find(InEnemy);
    if (Index != INDEX_NONE)
    {
        if(InEnemy)
        {
            InEnemy->GetController()->UnPossess();
            InEnemy->SetActorHiddenInGame(true);
            InEnemy->SetActorEnableCollision(false);
            InEnemy->SetActorTickEnabled(false);
            if(!ActiveEnemies.IsEmpty())
                ActiveEnemies.RemoveAt(Index);
            InEnemy->Reset();
            Pool.Add(InEnemy);
            
            if (CDSubsystem)
            {
                CDSubsystem->AddPurification(InEnemy->PurificationScore);
            }
        }
    }
}
