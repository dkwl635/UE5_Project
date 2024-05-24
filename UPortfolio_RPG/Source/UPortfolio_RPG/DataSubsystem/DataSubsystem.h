// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Item/ItemData.h"
#include "Enemy/EnemyData.h"
#include "Components/StatusComponent.h"
#include "DataSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API UDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UDataSubsystem();
	~UDataSubsystem();
	
public:
	static UDataSubsystem* DataSubsystem;// = nullptr;

	void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable)
	void Init();
public:
	
	FItemData* FindItem(const FName& InKey);
	FPotionData* FindPotionData(const FName& InKey);
	FEnemyData* FindEnemyData(const FName& InKey);
	FStatusDataTableRow* FindEnemyStatusData(const FName& InKey);
	FGearData* FindGearData(const FName& InKey);

protected:

	bool bInit = false;

//ITEM
	UPROPERTY()
	UDataTable* DT_Item;

	UPROPERTY()
	UDataTable* DT_Potion;

	UPROPERTY()
	UDataTable* DT_Gear;


// Enemy
	UPROPERTY()
	UDataTable* DT_Enemy;

	UPROPERTY()
	UDataTable* DT_EnemyStatus;

};
