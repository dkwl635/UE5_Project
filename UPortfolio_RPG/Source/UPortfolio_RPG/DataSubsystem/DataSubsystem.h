// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Item/ItemData.h"
#include "Enemy/EnemyData.h"
#include "Data/TextTable.h"
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
	void Initialize(FSubsystemCollectionBase& Collection) override;
	UFUNCTION(BlueprintCallable)
	void Init();
public:
	
	FItemData* FindItem(const FName& InKey);
	FPotionData* FindPotionData(const FName& InKey);
	FEnemyData* FindEnemyData(const FName& InKey);
	FStatusDataTableRow* FindEnemyStatusData(const FName& InKey);
	FGearData* FindGearData(const FName& InKey);
	FStringData* FindStringData(const FName& InKey);

protected:

	bool bInit = false;

	UDataTable* DT_Item;
	UDataTable* DT_Potion;
	UDataTable* DT_Gear;
	UDataTable* DT_String;
	UDataTable* DT_Enemy;
	UDataTable* DT_EnemyStatus;

};
