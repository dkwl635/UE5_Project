// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerInventorySubsystem.h"
#include "DataSubsystem/DataSubsystem.h"
#include "Item.h"
#include "UI/RPGSlot.h"
#include "UI/UIManager.h"

int32 UPlayerInventorySubsystem::GetPlayerCoin()
{
	return PlayerCoin;
}

int32 UPlayerInventorySubsystem::GetPlayerGold()
{
	return PlayerGold;
}

int32 UPlayerInventorySubsystem::GetEnchantStone()
{
	return EnchantStone;
}

void UPlayerInventorySubsystem::SetPlayerCoin(int32 Value)
{
	PlayerCoin = Value;
	AUIManager::UIManager->PlayerGoodsUIRefresh();
}

void UPlayerInventorySubsystem::SetPlayerGold(int32 Value)
{
	PlayerGold = Value;
	AUIManager::UIManager->PlayerGoodsUIRefresh();
}

void UPlayerInventorySubsystem::SetPlayerEnchantStone(int32 Value)
{
	EnchantStone = Value;
	AUIManager::UIManager->PlayerGoodsUIRefresh();
}

UPlayerInventorySubsystem::UPlayerInventorySubsystem()
{

}

UPlayerInventorySubsystem::~UPlayerInventorySubsystem()
{
	PlayerInventorySubsystem = nullptr;
}

void UPlayerInventorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	PlayerInventorySubsystem = this;

	NormalInventory.Init(nullptr, MaxInvenSize);
	GearInventory.Init(nullptr, MaxInvenSize);
	EquipmentInventory.Init(nullptr,7);
	QuickItemSlotsPointer.Init(-1, 8);


	DataSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDataSubsystem>();
	if (ItemClass) { ItemClass = UItem::StaticClass()->GetDefaultObject<UItem>(); }

	PlayerGold = 10000;
	PlayerCoin = 10000;
	
	AddItem(TEXT("HP100"), 12);
	AddItem(TEXT("HP500"), 3);
	AddItem(TEXT("Sword_0"), 1);
	AddItem(TEXT("Sword_1"), 1);
	AddItem(TEXT("Sword_1"), 1);
	AddItem(TEXT("Head_0"), 1);
	AddItem(TEXT("Armor_0"), 1);
	AddItem(TEXT("Pants_0"), 1);
	AddItem(TEXT("Shoes_1"), 1);
	AddItem(TEXT("Gloves_1"), 1);
}

bool UPlayerInventorySubsystem::Init()
{	
	return true;
}

bool UPlayerInventorySubsystem::AddItem(const FName& InKey, int8 Count = 1)
{
	FItemData* Data = DataSubsystem->FindItem(InKey);
	if (!Data) { return false; }

	Inventory Inventory = GetInventory(Data->ItemType);

	if (!IsAddable(Inventory ,Data, Count)) { return false; }

	MoveItemToInventory(Inventory, Data, Count);

	
	return	true;
}

bool UPlayerInventorySubsystem::IsAddable(Inventory Inventory,FItemData* ItemData, int8 Count)
{
	
	FName ItemName = ItemData->ItemName;
	int8 RemainingCount = Count;
	int8 InvenSize = MaxInvenSize;
	int8 CheckInvenIndex = FindItemInInventory(Inventory,ItemName, 0);

	while (CheckInvenIndex < InvenSize)
	{
		if (CheckInvenIndex >= InvenSize) { break; }
		
		int EmptySize = (*Inventory)[CheckInvenIndex]->MaxBundleCount - (*Inventory)[CheckInvenIndex]->CurrentBundleCount;

		RemainingCount -= EmptySize;
		if (RemainingCount <= 0) { return  true; }
		CheckInvenIndex = FindItemInInventory(Inventory,ItemName, CheckInvenIndex + 1);
	}
		
	int8 EmptyIndex = FindEmptyInventory(Inventory,0);

	while (EmptyIndex < InvenSize)
	{
		RemainingCount -= ItemData->MaxBundleCount;
		if (RemainingCount <= 0) { return  true; }

		EmptyIndex = FindEmptyInventory(Inventory,EmptyIndex+1);
	}

	if (RemainingCount <= 0) { return  true; }

	return false;
}

int8 UPlayerInventorySubsystem::FindItemInInventory(Inventory Inventory, const FName& ItemName, int8 StartIndex = 0)
{
	int8 Size = MaxInvenSize;
	for (int8 i = StartIndex; i < Size; i++)
	{
		TSharedPtr<FItemData> ItemData = (*Inventory)[i];
		if (ItemData == nullptr) { continue; }
		if (ItemData->ItemName == ItemName) 
		{
			if (ItemData->CurrentBundleCount < ItemData->MaxBundleCount) { return i; }
		
			continue;
		}
	}
	return Size;
}

int8 UPlayerInventorySubsystem::FindEmptyInventory(Inventory Inventory , int8 StartIndex = 0)
{
	int8 Size = MaxInvenSize;
	for (int8 i = StartIndex; i < Size; i++)
	{
		if ((*Inventory)[i] == nullptr) { return i; }
	}
	return Size;
}

bool UPlayerInventorySubsystem::MoveItemToInventory(Inventory Inventory ,FItemData* ItemData, int8 Count)
{	
	FName ItemName = ItemData->ItemName;
	int8 RemainingCount = Count;	
	int8 InvenSize = MaxInvenSize;
	int8 CheckInvenIndex = FindItemInInventory(Inventory,ItemName);
	while (CheckInvenIndex < InvenSize)
	{
		if (CheckInvenIndex >= InvenSize) { break; }
			
		int8 EmptySize = (*Inventory)[CheckInvenIndex]->MaxBundleCount - (*Inventory)[CheckInvenIndex]->CurrentBundleCount;
		if (EmptySize > 0)
		{
			int8 AddCount = 0;
			if (EmptySize > RemainingCount)
			{
				AddCount = RemainingCount;
				RemainingCount = 0;
			}
			else if (EmptySize <= RemainingCount)
			{
				AddCount = EmptySize;
				RemainingCount -= AddCount;
			}
			(*Inventory)[CheckInvenIndex]->CurrentBundleCount += AddCount;
		}

		if (RemainingCount <= 0) { return  true; }
	
		CheckInvenIndex = FindItemInInventory(Inventory, ItemName , CheckInvenIndex+1);
	}

	int8 EmptyIndex = FindEmptyInventory(Inventory);
	while (EmptyIndex < InvenSize)
	{
		int8 AddCount = 0;
		if (ItemData->MaxBundleCount > RemainingCount)
		{
			AddCount = RemainingCount;
			RemainingCount = 0;
		}
		else if (ItemData->MaxBundleCount <= RemainingCount)
		{
			AddCount = ItemData->MaxBundleCount;
			RemainingCount -= AddCount;
		}
		
		TSharedPtr<FItemData> NewItemData = MakeShared<FItemData>(*ItemData);
		NewItemData->CurrentBundleCount = AddCount;
		(*Inventory)[EmptyIndex] = NewItemData;

		if (RemainingCount <= 0) { return  true; }

		EmptyIndex = FindEmptyInventory(Inventory , EmptyIndex+1);
	}

	return false;
}

void UPlayerInventorySubsystem::RefreshUI(ERPG_UI UIType)
{
	AUIManager::UIManager->RefreshUI(UIType);
}

void UPlayerInventorySubsystem::UseItem(EITEMTYPE ItemType, int8 InventoryIndex , int8 Count)
{
	Inventory Inventory = GetInventory(ItemType);

	if (!Inventory || Count <= 0) { return; }
	
	FItemData* data = (*Inventory)[InventoryIndex].Get();
	if(!data) { return; }
	

	int NewCount = (data->CurrentBundleCount - Count);
	if (NewCount <= 0)
	{
		(*Inventory)[InventoryIndex] = nullptr;

		if (int QuickSlotIndex = CheckQuickSlotItem(InventoryIndex) != -1)
		{
			QuickItemSlotsPointer[QuickSlotIndex] = -1;
		}

	}
	else { data->CurrentBundleCount = NewCount; }

	RefreshUI(ERPG_UI::QUICKSLOTS);
	RefreshUI(ERPG_UI::INVENTORY);
	UseItem(data, Count);
	GEngine->ForceGarbageCollection(true);
}

void UPlayerInventorySubsystem::RemoveItem(EITEMTYPE ItemType, int8 InventoryIndex, int8 Count)
{
	Inventory Inventory = GetInventory(ItemType);

	if (!Inventory || Count <= 0) { return; }

	(*Inventory)[InventoryIndex] = nullptr;
	GEngine->ForceGarbageCollection(true);

	if (ItemType != EITEMTYPE::GEAR)
	{
		if (int QuickSlot = CheckQuickSlotItem(InventoryIndex) != -1)
		{
			QuickSlotClear(QuickSlot);
			AUIManager::UIManager->RefreshUI(ERPG_UI::QUICKSLOTS);
		}
	}
}


void UPlayerInventorySubsystem::UseItem(FItemData* ItemData, int8 Count)
{
	ItemClass->UseItem(nullptr, ItemData);
}

TWeakPtr<FItemData> UPlayerInventorySubsystem::GetItemInfo(EITEMTYPE ItemType, int8 InventoryIndex)
{
	Inventory Inventory = GetInventory(ItemType);
	if (InventoryIndex < 0 || !Inventory) { return nullptr; }

	return (*Inventory)[InventoryIndex];
}

void UPlayerInventorySubsystem::SwapItem(EITEMTYPE ItemType, int8 Index1, int8 Index2)
{
	Inventory Inventory = GetInventory(ItemType);

	TSharedPtr<FItemData>& thisItemData = (*Inventory)[Index1];
	TSharedPtr<FItemData>& StartItemData = (*Inventory)[Index2];

	
	
	bool bSwap = false;
	bool bCombine = false;
	if (thisItemData != nullptr && StartItemData != nullptr)
	{
		if (thisItemData->Unique_ID == StartItemData->Unique_ID)
		{
			if(CombineItem(ItemType, Index1, Index2) )
			{
				//bCombine = true;
			}
		}
		else { bSwap = true; }
	}
	else { bSwap = true; }

	if (bSwap)
	{
		Swap(thisItemData, StartItemData);	
		if (ItemType != EITEMTYPE::GEAR)
		{
			int QuickSlotIndex1 = CheckQuickSlotItem(Index1);
			int QuickSlotIndex2 = CheckQuickSlotItem(Index2);

			if (QuickSlotIndex1 != -1) { SetAttachQuickSlot(QuickSlotIndex1, Index2); }
			if (QuickSlotIndex2 != -1) { SetAttachQuickSlot(QuickSlotIndex2, Index1); }
		}
	}

	AUIManager::UIManager->RefreshUI(ERPG_UI::QUICKSLOTS);
}

bool UPlayerInventorySubsystem::CombineItem(EITEMTYPE ItemType ,int8 Index1, int8 Index2)
{
	Inventory Inventory = GetInventory(ItemType);

	TSharedPtr<FItemData>& ItemData1 = (*Inventory)[Index1];
	TSharedPtr<FItemData>& ItemData2 = (*Inventory)[Index2];

	if (ItemData1->Unique_ID == ItemData2->Unique_ID)
	{
		if (ItemData1->CurrentBundleCount == ItemData1->MaxBundleCount) { return false; }

		if (ItemData1->CurrentBundleCount < ItemData1->MaxBundleCount)
		{
			int8 temp = ItemData1->CurrentBundleCount + ItemData2->CurrentBundleCount;
			if (temp <= ItemData1->MaxBundleCount)
			{
				ItemData1->CurrentBundleCount = temp;
				ItemData2 = nullptr;
			}
			else
			{
				ItemData1->CurrentBundleCount = ItemData1->MaxBundleCount;
				ItemData2->CurrentBundleCount = temp - ItemData1->MaxBundleCount;
			}
		}
	}
	return true;
}

FItemData* UPlayerInventorySubsystem::ChangeGear(EGEARTYPE GearType,int8 Index)
{
	FItemData* OrginData = (EquipmentInventory[(int)GearType]).Get();
	
	TSharedPtr<FItemData>& NewGear =  GearInventory[Index];
	TSharedPtr<FItemData>& OldGear = EquipmentInventory[(int)GearType];

	Swap(NewGear, OldGear);

	RefreshUI(ERPG_UI::EQUIPMENT);
	RefreshUI(ERPG_UI::INVENTORY);

	return OrginData;
}

bool UPlayerInventorySubsystem::DeEquipment(EGEARTYPE GearType)
{
	TSharedPtr<FItemData>& OldGear = EquipmentInventory[(int)GearType];

	int InvenIndex = FindEmptyInventory(GetInventory(EITEMTYPE::GEAR) ,  0);
	if (InvenIndex >= MaxInvenSize) { return false; }

	ChangeGear(GearType, InvenIndex);
	RefreshUI(ERPG_UI::INVENTORY);
	RefreshUI(ERPG_UI::EQUIPMENT);
	return  true;
}

FItemData* UPlayerInventorySubsystem::GetNormalItem(int8 InvenIndex)
{
	return NormalInventory[InvenIndex].Get();
}

FItemData* UPlayerInventorySubsystem::GetGearItem(int8 InvenIndex)
{
	return GearInventory[InvenIndex].Get();
}

FItemData* UPlayerInventorySubsystem::GetEquipmentItem(int8 InvenIndex)
{
	return EquipmentInventory[InvenIndex].Get();
}

TArray<TSharedPtr<FItemData>>* UPlayerInventorySubsystem::GetInventory(EITEMTYPE ItemType)
{
	if (ItemType == EITEMTYPE::GEAR) { return &GearInventory; }
	else { return &NormalInventory; }
}

int32 UPlayerInventorySubsystem::GetPlayerAddAttack()
{
	int32 Result = 0;
	for (int i = 0; i < EquipmentInventory.Num(); i++)
	{
		if (!EquipmentInventory[i]){continue;}

		FGearData* data  = DataSubsystem->FindGearData( EquipmentInventory[i]->StatusData.RowName);
		if (data->EStat == ESTAT::ATK)
		{
			Result += data->GearValue;
		}
	}

	return Result;
}

int32 UPlayerInventorySubsystem::GetPlayerAddMaxHp()
{
	int32 Result = 0;
	for (int i = 0; i < EquipmentInventory.Num(); i++)
	{
		if (!EquipmentInventory[i]) { continue; }

		FGearData* data = DataSubsystem->FindGearData(EquipmentInventory[i]->StatusData.RowName);
		if (data->EStat == ESTAT::HP)
		{
			Result += data->GearValue;
		}
	}

	return Result;
}

void UPlayerInventorySubsystem::SetAttachQuickSlot(int QuickSlotIndex, int ItemIndex)
{
	QuickItemSlotsPointer[QuickSlotIndex] = ItemIndex;
}

void UPlayerInventorySubsystem::AttachSlot(ERPGSLOTTYPE SlotType , URPGSlot* slot)
{
	switch (SlotType)
	{
	case ERPGSLOTTYPE::QUICK_ITEM:
	{
		QuickItemSlots.Add(slot);
		break;
	}
	default:
		break;
	}
}

int UPlayerInventorySubsystem::GetQuickSlotFromIndex(int QuickSlotIndex)
{
	return QuickItemSlotsPointer[QuickSlotIndex];
}

void UPlayerInventorySubsystem::QuickSlotClear(int8 QuickSlotIndex)
{
	QuickItemSlotsPointer[QuickSlotIndex] = -1;
}

int UPlayerInventorySubsystem::CheckQuickSlotItem(int ItemIndex)
{
	for (int8 i = 0; i < QuickItemSlotsPointer.Num(); i++)
	{
		if (QuickItemSlotsPointer[i] == ItemIndex) { return i; }
	}

	return -1;
}


