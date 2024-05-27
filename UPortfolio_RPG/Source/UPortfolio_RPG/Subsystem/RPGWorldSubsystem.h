// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "RPGWorldSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API URPGWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	URPGWorldSubsystem();

public:
	void OnWorldBeginPlay(UWorld& InWorld) override;
	void Deinitialize() override;
	
	TSubclassOf<AActor> NPCManagerBP;
	TSubclassOf<AActor> DropItemManagerBP;
	TSubclassOf<AActor> UIManagerBP;

	class ANPCManager* NPCManager;
	class ADropItemManager* DropItemManager;
	class AUIManager* UIManager;
	

};
