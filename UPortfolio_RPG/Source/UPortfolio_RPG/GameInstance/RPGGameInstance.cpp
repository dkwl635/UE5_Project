// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstance/RPGGameInstance.h"
#include "DataSubsystem/DataSubsystem.h"
#include "UI/UIManager.h"
#include "NPC/NPCManager.h"
#include "Components/DropItemManager.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Actors/PlayerCharacter/PlayerCharacter.h"
#include "Actors/Controller/BasicPlayerController.h"
#include "Item/PlayerInventorySubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystem/RPGWorldSubsystem.h"


TWeakObjectPtr<URPGGameInstance> RPGGameInstance = nullptr;
void URPGGameInstance::Init()
{
	Super::Init();
	RPGGameInstance = this;
}

void URPGGameInstance::FinishDestroy()
{
	RPGGameInstance = nullptr;
	PlayerInventorySubsystem = nullptr;
	Super::FinishDestroy();
}


UPlayerInventorySubsystem* URPGGameInstance::GetPlayerInventorySubsystem()
{
	if (PlayerInventorySubsystem == nullptr)
	{
		PlayerInventorySubsystem = GetSubsystem<UPlayerInventorySubsystem>();
	}

	return PlayerInventorySubsystem.Get();
}

UDataSubsystem* URPGGameInstance::GetDataSubsyetem()
{
	if (DataSubsystem == nullptr)
	{
		DataSubsystem = GetSubsystem<UDataSubsystem>();
	}
	return DataSubsystem.Get();
}

AUIManager* URPGGameInstance::GetUIManager()
{
	return GetCurrentWorld()->GetSubsystem<URPGWorldSubsystem>()->UIManager; //RPGGameInstance->GetUIManager().Get();
}
ANPCManager* URPGGameInstance::GetNPCManager()
{
	return GetCurrentWorld()->GetSubsystem<URPGWorldSubsystem>()->NPCManager; // ANPCManager::NPCManager;
}

ADropItemManager* URPGGameInstance::GetDropItemManager()
{
	return GetCurrentWorld()->GetSubsystem<URPGWorldSubsystem>()->DropItemManager;// ADropItemManager::DropItemManager.Get();
}

APlayerCharacter* URPGGameInstance::GetPlayerCharacter()
{
	//UWorld* World = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport)->World();
	UWorld* World = GetCurrentWorld();
	ACharacter* Character = UGameplayStatics::GetPlayerCharacter(GetCurrentWorld(), 0);
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Character);
	return PlayerCharacter;
}

UWorld* URPGGameInstance::GetCurrentWorld()
{
	return GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport)->World();
}

ABasicPlayerController* URPGGameInstance::GetPlayerBasicController()
{
	UWorld* World = GetCurrentWorld();
	APlayerController* Controller =  UGameplayStatics::GetPlayerController(World, 0);
	ABasicPlayerController* BasicPlayerController = Cast<ABasicPlayerController>(Controller);

	return BasicPlayerController;
}