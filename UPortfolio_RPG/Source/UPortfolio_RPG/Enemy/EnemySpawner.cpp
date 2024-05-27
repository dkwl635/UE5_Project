// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/EnemySpawner.h"
#include "Enemy/EnemyPool.h"
#include "NavigationSystem.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	EnemyPool = NewObject<UEnemyPool>();
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	EnemyPool->Create(GetWorld(), MaxPoolNum);
}

void AEnemySpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	EnemyPool->Destroy();

	Super::EndPlay(EndPlayReason);
}

void AEnemySpawner::SpawnEnemy()
{
	FVector Origin = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	FVector RandomLocation;
	
	SpawnNum = FMath::RandRange(10, 15);
	int32 SpawnedEnemyNum = EnemyPool->ActiveEnemies.Num();
	if (SpawnedEnemyNum <= MaxPoolNum)
	{
		for(int32 i=0;i<SpawnNum;++i)
		{
			if (EnemyPool->ActiveEnemies.Num() == MaxPoolNum)
				break;
			UNavigationSystemV1::K2_GetRandomReachablePointInRadius(GetWorld(), Origin, RandomLocation, 2000.f);
			RandomLocation.Z = 300.f;
			FTransform Transform = FTransform(FRotator::ZeroRotator, RandomLocation, FVector(1, 1, 1));
			EnemyPool->SpawnEnemy(Transform, true);
		}
	}
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

