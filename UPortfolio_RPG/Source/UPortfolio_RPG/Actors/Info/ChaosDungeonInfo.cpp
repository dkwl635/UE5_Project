// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Info/ChaosDungeonInfo.h"
#include "Actors/Controller/CD_PlayerController.h"
#include "Enemy/EnemySpawner.h"

void AChaosDungeonInfo::BeginPlay()
{
	Super::BeginPlay();
	
	InitChaosDungeon();
}

void AChaosDungeonInfo::InitChaosDungeon()
{
	AEnemySpawner* Spawner = GetWorld()->SpawnActor<AEnemySpawner>();
}							
