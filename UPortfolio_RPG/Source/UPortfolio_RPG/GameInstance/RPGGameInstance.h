// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "RPGGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API URPGGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	void Init() override;
	void FinishDestroy() override;
private:
	TWeakObjectPtr<UPlayerInventorySubsystem> PlayerInventorySubsystem;
	TWeakObjectPtr<UDataSubsystem> DataSubsystem;
public:

	UFUNCTION(BlueprintCallable)
	class UPlayerInventorySubsystem* GetPlayerInventorySubsystem();

	UFUNCTION(BlueprintCallable)
	class UDataSubsystem* GetDataSubsyetem();
	
	UFUNCTION(BlueprintCallable)
	class AUIManager* GetUIManager();

	UFUNCTION(BlueprintCallable)
	class ANPCManager* GetNPCManager();

	UFUNCTION(BlueprintCallable)
	class ADropItemManager* GetDropItemManager();

	UFUNCTION(BlueprintCallable)
	class APlayerCharacter* GetPlayerCharacter();

	UFUNCTION(BlueprintCallable)
	class ABasicPlayerController* GetPlayerBasicController();
	
	UFUNCTION(BlueprintCallable)
	UWorld* GetCurrentWorld();




};
extern TWeakObjectPtr<URPGGameInstance> RPGGameInstance;