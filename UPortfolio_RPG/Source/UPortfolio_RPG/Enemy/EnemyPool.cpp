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
    ControllerPool.Reserve(Count);
    ActiveEnemies.Reserve(Count);
    CachedWorld = World;

    for (uint32 i = 0; i < Count; ++i)
    {
        AEnemy* NewEnemy = World->SpawnActor<AEnemy>(FVector::ZeroVector,FRotator::ZeroRotator);
        if (NewEnemy)
        {
            NewEnemy->SetActorHiddenInGame(true); // Render off
            NewEnemy->SetActorEnableCollision(false); // Collision off
            NewEnemy->SetActorTickEnabled(false); // Tick off
            AEnemyAIController* EnemyController = Cast<AEnemyAIController>(NewEnemy->GetController());
            ControllerPool.Add(EnemyController);

            EnemyController->UnPossess();
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
    for (auto* It : ControllerPool)
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
    AEnemyAIController* EnemyController = nullptr;

    if (Pool.Num() > 0 && ActiveEnemies.Num()<30)
    {
        Enemy = Pool.Pop(false);
        EnemyController = ControllerPool.Pop(false);
        if(Enemy && EnemyController)
        {
            ActiveEnemies.Add(Enemy);
            Enemy->SetOwner(Owner);
            Enemy->SetInstigator(Instigator);
            Enemy->SetPool(this);
            Enemy->SetActorHiddenInGame(false);
            Enemy->SetActorEnableCollision(bEnableCollision);
            Enemy->SetActorTickEnabled(true);
            Enemy->PurificationScore = FMath::RandRange(100, 200);
            Enemy->SetActorTransform(InTransform);
            EnemyController->OnPossess(Enemy);

            UEnemyAnimInstance* AnimInstance = Enemy->GetAnimInstance();
            if (AnimInstance)
                AnimInstance->PlaySpawnMontage();
        }
    }
    return Enemy;
}

void UEnemyPool::Delete(AEnemy* InEnemy)
{
    const int32 Index = ActiveEnemies.Find(InEnemy);
    if (Index != INDEX_NONE)
    {
        if(InEnemy)
        {
            AEnemyAIController* EnemyController = Cast<AEnemyAIController>(InEnemy->GetController());
            if(EnemyController)
                ControllerPool.Add(EnemyController);
            EnemyController->UnPossess();
            InEnemy->SetActorHiddenInGame(true);
            InEnemy->SetActorEnableCollision(false);
            InEnemy->SetActorTickEnabled(false);
            if(!ActiveEnemies.IsEmpty())
                ActiveEnemies.RemoveAt(Index);
            InEnemy->Reset();
            Pool.Add(InEnemy);
            if (IsValid(CachedWorld))
            {
                UChaosDungeonSubsystem* CDSubsystem = CachedWorld->GetSubsystem<UChaosDungeonSubsystem>();
                ensure(CDSubsystem);
                if (CDSubsystem)
                {
                    CDSubsystem->AddPurification(InEnemy->PurificationScore);
                }
            }
        }
    }
}
