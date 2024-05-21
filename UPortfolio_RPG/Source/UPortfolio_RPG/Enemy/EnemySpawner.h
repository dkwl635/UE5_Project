// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class UEnemyPool;

UCLASS()
class UPORTFOLIO_RPG_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:
	UFUNCTION(BlueprintCallable)
	void SpawnEnemy();
	UEnemyPool* GetEnemyPool() { return EnemyPool; }
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY()
	UEnemyPool* EnemyPool = nullptr;
	const int32 MaxPoolNum = 30;
	int32 SpawnNum = 0;
};
