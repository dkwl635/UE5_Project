// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UI/Slot/SlotEnum.h"
#include "PlayerInventorySubsystem.generated.h"

/**
 * 
 */
//struct  FItemData;

UCLASS()
class UPORTFOLIO_RPG_API UPlayerInventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	typedef  TArray<TSharedPtr<FItemData>>* Inventory;
	class URPGSlotUserWidget;
public : 
	UPlayerInventorySubsystem();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	bool Init();
	//아이템 추가
	bool AddItem(const FName& InKey, int8 Count);
	//아이템 사용
	void UseItem(EITEMTYPE ItemType, int8 InventoryIndex, int8 Count);
	void UseItem(FItemData* ItemData, int8 Count);
	//아이템 가져오기
	TWeakPtr<FItemData> GetItemInfo(EITEMTYPE ItemType, int8 InventoryIndex);
	//아이템 위치 바꾸기
	void SwapItem(EITEMTYPE ItemType , int8 index1, int8 index2);

private:

	//아이템 추가가 가능한지
	bool IsAddable(Inventory Inventory, FItemData* ItemData, int8 Count);
	//같은 아이템 찾기
	int8 FindItemInInventory(Inventory Inventory, const FName& InKey, int8 StartIndex);
	//빈공간 찾기
	int8 FindEmptyInventory(Inventory Inventory, int8 StartIndex);

	//아이템 타입에 맞는 가방 리턴
	Inventory GetInventory(EITEMTYPE ItemType);

	//(AddItem 안에서 호출) 추가되는 아이템 가방에 추가
	bool MoveItemToInventory(Inventory Inventory, FItemData* ItemData, int8 Count);

public:

	void AttachSlot(ERPGSLOTTYPE SlotType , URPGSlotUserWidget* Slot);

	void QuickSlotRefresh(int8 QuickSlotIndex);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UUserWidget* DragSlot;

private:


	const int8 MaxInvenSize = 60;
	TArray<TSharedPtr<FItemData>> GearInventory;
	TArray<TSharedPtr<FItemData>> NormalInventory;


	TArray<TWeakObjectPtr<URPGSlotUserWidget>> GearSlots;
	TArray<TWeakObjectPtr<URPGSlotUserWidget>> NormalSlots;



	
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
