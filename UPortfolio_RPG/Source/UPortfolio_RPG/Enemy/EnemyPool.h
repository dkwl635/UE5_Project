// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enemy/Enemy.h"
#include "EnemyPool.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API UEnemyPool : public UObject
{
	GENERATED_BODY()
public:
    UEnemyPool();

    void Create(UWorld* World, uint32 Count);
    void Destroy();

    AEnemy* SpawnEnemy(const FTransform& InTransform, bool bEnableCollision = true, AActor* Owner = nullptr, APawn* Instigator = nullptr);

    void Delete(AEnemy* InEnemy);

    TArray<AEnemy*> Pool;
    TArray<AEnemy*> ActiveEnemies;

private:
    //list로 액터 관리.. 
    TSubclassOf<AEnemy> EnemyClass;
};
	
