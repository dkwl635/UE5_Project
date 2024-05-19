// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/ChaosDungeon/ChaosDungeonSubsystem.h"
#include "Enemy/EnemySpawner.h"
#include "Enemy/EnemyPool.h"

UChaosDungeonSubsystem::UChaosDungeonSubsystem()
{
}

void UChaosDungeonSubsystem::StartDungeon()
{
	if (!bIsStarted)
	{
		bIsStarted = true;
		Spawner = GetWorld()->SpawnActor<AEnemySpawner>();
		GetWorld()->GetTimerManager().SetTimer(DungeonLimitTimer, this, &UChaosDungeonSubsystem::EndDungeon, TimeLimit, false);
		GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &UChaosDungeonSubsystem::SpawnEnemy, SpawnInterval, true);
	}
}

void UChaosDungeonSubsystem::EndDungeon()
{
	GetWorld()->GetTimerManager().ClearTimer(SpawnTimer);
	GetWorld()->GetTimerManager().ClearTimer(DungeonLimitTimer);
	UE_LOG(LogTemp, Warning, TEXT("Dungeon Ended!"));
	Spawner->GetEnemyPool()->Destroy();
}

void UChaosDungeonSubsystem::SpawnEnemy()
{
	UE_LOG(LogTemp, Warning, TEXT("Spawn Started!"));
	Spawner->SpawnEnemy();
}

void UChaosDungeonSubsystem::AddPurification(int32 InValue)
{
	Purification += InValue;
	UE_LOG(LogTemp, Warning, TEXT("Purification : %d"), Purification);
	if (Purification >= 20000)
	{
		EndDungeon();
	}
}