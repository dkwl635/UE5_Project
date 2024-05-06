// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemyPool.h"

UEnemyPool::UEnemyPool()
{
    EnemyClass = AEnemy::StaticClass();
}

void UEnemyPool::Create(UWorld* World, uint32 Count)
{
    for (uint32 i = 0; i < Count; ++i)
    {
        AEnemy* NewEnemy = World->SpawnActor<AEnemy>(EnemyClass, FVector::ZeroVector, FRotator::ZeroRotator);
        Pool.Add(NewEnemy);
    }
}

void UEnemyPool::Destroy()
{
    for (AEnemy* Enemy : Pool)
    {
        if (Enemy)
        {
            Enemy->Destroy();
        }
    }
    Pool.Empty();
}

AEnemy* UEnemyPool::SpawnEnemy(const FTransform& InTransform, bool bEnableCollision, AActor* Owner, APawn* Instigator)
{
    AEnemy* Enemy = nullptr;
    if (Pool.Num() > 0)
    {
        Enemy = Pool.Pop(false);
        ActiveEnemies.Add(Enemy);
        Enemy->SetOwner(Owner);
        Enemy->SetInstigator(Instigator);
        Enemy->SetActorEnableCollision(bEnableCollision);
        Enemy->SetActorHiddenInGame(false);
        Enemy->SetActorTickEnabled(true);
        Enemy->SetActorTransform(InTransform);
    }
    return Enemy;
}

void UEnemyPool::Delete(AEnemy* InEnemy)
{
    const int32 Index = ActiveEnemies.Find(InEnemy);
    if (Index != INDEX_NONE)
    {
        ActiveEnemies.RemoveAt(Index);
        Pool.Add(InEnemy);
    }
}
