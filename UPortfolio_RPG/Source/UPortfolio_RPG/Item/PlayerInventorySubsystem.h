// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UI/Slot/SlotEnum.h"
#include "ItemEnum.h"
#include "PlayerInventorySubsystem.generated.h"


UCLASS()
class UPORTFOLIO_RPG_API UPlayerInventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	typedef  TArray<TSharedPtr<struct FItemData>>* Inventory;

private:

	UPROPERTY(EditAnywhere)
	int32 PlayerCoin = 0;
	UPROPERTY(EditAnywhere)
	int32 PlayerGold = 0;
	UPROPERTY(EditAnywhere)
	int32 EnchantStone = 0;
public:
	int32 GetPlayerCoin();
	int32 GetPlayerGold();
	int32 GetEnchantStone();

	void SetPlayerCoin(int32 Value);
	void SetPlayerGold(int32 Value);
	void SetPlayerEnchantStone(int32 Value);

private:
	const int8 MaxInvenSize = 30;
	TArray<TSharedPtr<FItemData>> GearInventory;
	TArray<TSharedPtr<FItemData>> NormalInventory;
public:
	TArray<TSharedPtr<FItemData>> EquipmentInventory;
public : 
	UPlayerInventorySubsystem();
	~UPlayerInventorySubsystem();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	UFUNCTION(BlueprintCallable)
	bool Init();
	bool AddItem(const FName& InKey, int8 Count);	
	void UseItem(EITEMTYPE ItemType, int8 InventoryIndex, int8 Count = 1);
	void RemoveItem(EITEMTYPE ItemType, int8 InventoryIndex, int8 Count = 1);
	
	TWeakPtr<FItemData> GetItemInfo(EITEMTYPE ItemType, int8 InventoryIndex);
	void SwapItem(EITEMTYPE ItemType , int8 Index1, int8 Index2);
	bool CombineItem(EITEMTYPE ItemType, int8 Index1, int8 Index2);

	FItemData* ChangeGear(EGEARTYPE GearType , int8 Index1);
	bool DeEquipment(EGEARTYPE GearType);

	FItemData* GetNormalItem(int8 InvenIndex);
	FItemData* GetGearItem(int8 InvenIndex);
	FItemData* GetEquipmentItem(int8 InvenIndex);

private:
	void UseItem(FItemData* ItemData, int8 Count);
	bool IsAddable(Inventory Inventory, FItemData* ItemData, int8 Count);
	int8 FindItemInInventory(Inventory Inventory, const FName& InKey, int8 StartIndex);
	int8 FindEmptyInventory(Inventory Inventory, int8 StartIndex);
	Inventory GetInventory(EITEMTYPE ItemType);
	bool MoveItemToInventory(Inventory Inventory, FItemData* ItemData, int8 Count);

public:
	void RefreshUI(ERPG_UI UIType);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* DragSlot;

private:
	UPROPERTY()
	TArray<TWeakObjectPtr<class URPGSlot>> QuickItemSlots;

	TArray<int> QuickItemSlotsPointer;
	
public:
	int32 GetPlayerAddAttack();
	int32 GetPlayerAddMaxHp();
	

public:

	void SetAttachQuickSlot(int QuickSlotIndex, int ItemIndex);
	void AttachSlot(ERPGSLOTTYPE SlotType, class URPGSlot* Slot);
	int GetQuickSlotFromIndex(int QuickSlotIndex);
	int CheckQuickSlotItem(int ItemIndex);
	
	void QuickSlotClear(int8 QuickSlotIndex);


public:
	 class UDataSubsystem* DataSubsystem;
	class UItem* ItemClass;

public:
	bool bOpenShop = false;


};

extern UPlayerInventorySubsystem* PlayerInventorySubsystem = nullptr;