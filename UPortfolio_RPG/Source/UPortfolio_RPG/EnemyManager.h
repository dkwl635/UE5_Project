// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enemy/Enemy.h"
#include "EnemyManager.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API UEnemyManager : public UObject
{
	GENERATED_BODY()

public:
    UEnemyManager();

    // 스폰 관련 메서드
    void SpawnEnemy(const FVector& Location);
    void DespawnEnemy(AEnemy* Enemy);

private:
    // 오브젝트 풀 관련 멤버 변수
    TArray<AEnemy*> EnemyPool;
};
	
