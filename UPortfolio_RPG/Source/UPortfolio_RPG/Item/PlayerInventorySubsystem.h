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
	//������ �߰�
	bool AddItem(const FName& InKey, int8 Count);
	//������ ���
	void UseItem(EITEMTYPE ItemType, int8 InventoryIndex, int8 Count);
	void UseItem(FItemData* ItemData, int8 Count);
	//������ ��������
	TWeakPtr<FItemData> GetItemInfo(EITEMTYPE ItemType, int8 InventoryIndex);
	//������ ��ġ �ٲٱ�
	void SwapItem(EITEMTYPE ItemType , int8 index1, int8 index2);

private:

	//������ �߰��� ��������
	bool IsAddable(Inventory Inventory, FItemData* ItemData, int8 Count);
	//���� ������ ã��
	int8 FindItemInInventory(Inventory Inventory, const FName& InKey, int8 StartIndex);
	//����� ã��
	int8 FindEmptyInventory(Inventory Inventory, int8 StartIndex);

	//������ Ÿ�Կ� �´� ���� ����
	Inventory GetInventory(EITEMTYPE ItemType);

	//(AddItem �ȿ��� ȣ��) �߰��Ǵ� ������ ���濡 �߰�
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
