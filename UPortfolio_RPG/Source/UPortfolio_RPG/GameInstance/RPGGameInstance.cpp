// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/RPGGameInstance.h"
#include "DataSubsystem/DataSubsystem.h"
#include "UI/UIManager.h"
#include "NPC/NPCManager.h"
#include "Components/DropItemManager.h"
#include "Engine/World.h"
#include "Engine/Engine.h"



void URPGGameInstance::Init()
{
	Super::Init();
}




UDataSubsystem* URPGGameInstance::GetDataSubsyetem()
{
	
	return nullptr;
}

AUIManager* URPGGameInstance::GetUIManager()
{
	return AUIManager::UIManager.Get();
}
ANPCManager* URPGGameInstance::GetNPCManager()
{
	return ANPCManager::NPCManager;
}

ADropItemManager* URPGGameInstance::GetDropItemManager()
{
	return ADropItemManager::DropItemManager.Get();
}

