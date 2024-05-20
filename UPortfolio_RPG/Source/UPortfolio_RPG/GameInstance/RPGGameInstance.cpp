// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/RPGGameInstance.h"
#include "DataSubsystem/DataSubsystem.h"
#include "UI/UIManager.h"

UDataSubsystem* URPGGameInstance::GetDataSubsyetem()
{
	
	return nullptr;
}

AUIManager* URPGGameInstance::GetUIManager()
{
	return AUIManager::UIManager.Get();
}
