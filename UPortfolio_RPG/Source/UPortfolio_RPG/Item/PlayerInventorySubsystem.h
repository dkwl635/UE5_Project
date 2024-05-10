// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UI/Slot/SlotEnum.h"
#include "UI/RPGSlotUserWidget.h"
#include "PlayerInventorySubsystem.generated.h"



UCLASS()
class UPORTFOLIO_RPG_API UPlayerInventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	typedef  TArray<TSharedPtr<FItemData>>* Inventory;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PlayerCoin = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PlayerGold = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EnchantStone = 0;

private:
	const int8 MaxInvenSize = 30;
	TArray<TSharedPtr<FItemData>> GearInventory;
	TArray<TSharedPtr<FItemData>> NormalInventory;
public : 
	UPlayerInventorySubsystem();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	UFUNCTION(BlueprintCallable)
	bool Init();
	bool AddItem(const FName& InKey, int8 Count);	
	void UseItem(EITEMTYPE ItemType, int8 InventoryIndex, int8 Count);
	void UseItem(FItemData* ItemData, int8 Count);
	TWeakPtr<FItemData> GetItemInfo(EITEMTYPE ItemType, int8 InventoryIndex);
	void SwapItem(EITEMTYPE ItemType , int8 Index1, int8 Index2);
	bool CombineItem(EITEMTYPE ItemType, int8 Index1, int8 Index2);

private:
	bool IsAddable(Inventory Inventory, FItemData* ItemData, int8 Count);
	int8 FindItemInInventory(Inventory Inventory, const FName& InKey, int8 StartIndex);
	int8 FindEmptyInventory(Inventory Inventory, int8 StartIndex);
	Inventory GetInventory(EITEMTYPE ItemType);
	bool MoveItemToInventory(Inventory Inventory, FItemData* ItemData, int8 Count);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* DragSlot;

private:

	UPROPERTY()
	TArray<TWeakObjectPtr<URPGSlotUserWidget>> GearSlots;
	UPROPERTY()
	TArray<TWeakObjectPtr<URPGSlotUserWidget>> NormalSlots;
	UPROPERTY()
	TArray<TWeakObjectPtr<URPGSlotUserWidget>> QuickItemSlots;
		



public:

	void AttachSlot(ERPGSLOTTYPE SlotType, URPGSlotUserWidget* Slot);
	
	void QuickSlotRefresh(int8 QuickSlotIndex);
	URPGSlotUserWidget* CheckQuickSlotItem(URPGSlotUserWidget* Slot);

	
public:

	 class UDataSubsystem* DataSubsystem;
	 UItem* ItemClass;
};
