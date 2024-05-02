// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PlayerInventorySubsystem.generated.h"

/**
 * 
 */
typedef  TArray<TSharedPtr<FItemData>>* Inventory;
UCLASS()
class UPORTFOLIO_RPG_API UPlayerInventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()


public : 

	bool Init();
	
	bool AddItem(const FName& InKey, int8 Count);
	bool IsAddable(Inventory Inventory, FItemData* ItemData, int8 Count);
	int8 FindItemInInventory(Inventory Inventory ,const FName& InKey, int8 StartIndex);
	int8 FindEmptyInventory(Inventory Inventory ,int8 StartIndex);
	bool MoveItemToInventory(Inventory Inventory , FItemData* ItemData, int8 Count);
	void ClearTempData();
	void UseItem(Inventory Inventory , int8 InventoryIndex, int8 Count);

	FItemData* GetItemInfo(Inventory Inventory, int8 InventoryIndex);

	//아이템 타입에 맞는 가방 리턴
	Inventory GetInventory(EITEMTYPE ItemType);

	void QuickSlotRefresh(int8 QuickSlotIndex);



private:


	const int8 MaxInvenSize = 60;
	TArray<TSharedPtr<FItemData>> GearInventory;
	TArray<TSharedPtr<FItemData>> NormalInventory;

	class URPGSlotUserWidget;
	TArray<TSharedPtr<URPGSlotUserWidget>> GearSlots;
	TArray<TSharedPtr<URPGSlotUserWidget>> NormalSlots;
	
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
