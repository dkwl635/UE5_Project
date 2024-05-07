// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPCManager.generated.h"

UCLASS()
class UPORTFOLIO_RPG_API ANPCManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANPCManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void BeginOverlapPlayer(class ANPC* Target);
	void EndOverlapPlayer(class ANPC* Target);

};
