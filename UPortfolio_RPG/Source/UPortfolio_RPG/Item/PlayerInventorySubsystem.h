// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DataSubsystem/DataSubsystem.h"
#include "Item.h"
#include "PlayerInventorySubsystem.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API UPlayerInventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()


public : 

	bool Init();
	
	bool AddItem(const FName& InKey, int8 Count);
	bool IsAddable(FItemData* ItemData, int8 Count);
	int8 FindItemInInventory(const FName& InKey, int8 StartIndex);
	int8 FindEmptyInventory(int8 StartIndex);
	bool MoveItemToInventory(FItemData* ItemData, int8 Count);


private:
	const int8 MaxInvenSize = 60;
	TArray<TSharedPtr<FItemData>> Inventory;
	
public:

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	int32 PlayerCoin = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PlayerGold = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EnchantStone = 0;

	
public:

	UDataSubsystem* DataSubsystem;
	UItem* ItemClass;
};
