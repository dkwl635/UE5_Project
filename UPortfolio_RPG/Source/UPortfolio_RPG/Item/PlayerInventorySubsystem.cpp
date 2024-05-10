// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerInventorySubsystem.h"
#include "DataSubsystem/DataSubsystem.h"
#include "Item.h"

#include "UI/Slot/QuickItemSlotData.h"



UPlayerInventorySubsystem::UPlayerInventorySubsystem()
{

}

void UPlayerInventorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogTemp, Warning, TEXT("UPlayerInventorySubsystem :: Initialize"));

	NormalInventory.SetNum(MaxInvenSize, false);
	GearInventory.SetNum(MaxInvenSize, false);

	DataSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDataSubsystem>();
	if (ItemClass) { ItemClass = UItem::StaticClass()->GetDefaultObject<UItem>(); }
}

bool UPlayerInventorySubsystem::Init()
{	
	/*GearSlots.Empty();
	NormalSlots.Empty();
	QuickItemSlots.Empty();*/


	AddItem( TEXT("HP100"), 12);
	AddItem( TEXT("HP500"), 3);
	AddItem(TEXT("HP100"), 100);

	return true;
}

bool UPlayerInventorySubsystem::AddItem(const FName& InKey, int8 Count = 1)
{
	FItemData* Data = DataSubsystem->FindItem(InKey);
	if (!Data)
	{
		check(false);
		return false;
	}

	Inventory Inventory = GetInventory(Data->ItemType);

	//가방에 들어가는 체크
	if (!IsAddable(Inventory ,Data, Count))
	{
		return false;
	}

	return	MoveItemToInventory(Inventory ,Data, Count);

}

bool UPlayerInventorySubsystem::IsAddable(Inventory Inventory,FItemData* ItemData, int8 Count)
{
	
	FName ItemName = ItemData->ItemName;
	int8 RemainingCount = Count;
	int8 InvenSize = MaxInvenSize;
	int8 CheckInvenIndex = FindItemInInventory(Inventory,ItemName, 0);

	while (CheckInvenIndex < InvenSize)
	{
		if (CheckInvenIndex >= InvenSize)
			break;

		int EmptySize = (*Inventory)[CheckInvenIndex]->MaxBundleCount - (*Inventory)[CheckInvenIndex]->CurrentBundleCount;

		RemainingCount -= EmptySize;
	
		if (RemainingCount <= 0)
		{
			return  true;
		}

		CheckInvenIndex = FindItemInInventory(Inventory,ItemName, CheckInvenIndex + 1);
	}
	
	
	int8 EmptyIndex = FindEmptyInventory(Inventory,0);

	while (EmptyIndex < InvenSize)
	{
		RemainingCount -= ItemData->MaxBundleCount;
		if (RemainingCount <= 0)
		{
			return  true;
		}
		EmptyIndex = FindEmptyInventory(Inventory,EmptyIndex+1);
	}

	if (RemainingCount <= 0)
	{
		return  true;
	}

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
			if (ItemData->CurrentBundleCount < ItemData->MaxBundleCount)
			{
				return i;
			}
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
		if ( (*Inventory)[i]  == nullptr)
		{
			return i;
		}
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
		if (CheckInvenIndex >= InvenSize)
			break;
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
		if (RemainingCount <= 0)
		{
			return  true;
		}
		CheckInvenIndex = FindItemInInventory(Inventory, ItemName);
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
		//Create New Item
		TSharedPtr<FItemData> NewItemData = MakeShared<FItemData>(*ItemData);
		NewItemData->CurrentBundleCount = AddCount;
		(*Inventory)[EmptyIndex] = NewItemData;

		if (RemainingCount <= 0)
		{
			return  true;
		}
		EmptyIndex = FindEmptyInventory(Inventory);
	}

	//ensure(false);
	return false;
}



void UPlayerInventorySubsystem::UseItem(EITEMTYPE ItemType, int8 InventoryIndex , int8 Count = 1)
{
	Inventory Inventory = GetInventory(ItemType);

	if (!Inventory || Count <= 0)
	{
		return;
	}
	
	FItemData* data = (*Inventory)[InventoryIndex].Get();
	if(!data)
	{
		return;
	}

	int NewCount = (data->CurrentBundleCount - Count);
	if (NewCount <= 0)
	{
		(*Inventory)[InventoryIndex] = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("UseItem 00"));
	}
	else
	{
		data->CurrentBundleCount = NewCount;
	}

	UseItem(data, Count);
	GEngine->ForceGarbageCollection(true);
	
}

void UPlayerInventorySubsystem::UseItem(FItemData* ItemData, int8 Count)
{
	ItemClass->UseItem(nullptr, ItemData);
}

TWeakPtr<FItemData> UPlayerInventorySubsystem::GetItemInfo(EITEMTYPE ItemType, int8 InventoryIndex)
{
	Inventory Inventory = GetInventory(ItemType);
	if(InventoryIndex < 0 || !Inventory)
	{
		return nullptr;
	}

	return (*Inventory)[InventoryIndex];
}

void UPlayerInventorySubsystem::SwapItem(EITEMTYPE ItemType, int8 Index1, int8 Index2)
{
	Inventory Inventory = GetInventory(ItemType);

	TSharedPtr<FItemData>& thisItemData = (*Inventory)[Index1];
	TSharedPtr<FItemData>& StartItemData = (*Inventory)[Index2];

	if (thisItemData != nullptr && StartItemData != nullptr)
	{
		if (thisItemData->Unique_ID == StartItemData->Unique_ID)
		{
			if(!CombineItem(ItemType, Index1, Index2) )
			{
				Swap(thisItemData, StartItemData);
			}
		}
		else
		{
			Swap(thisItemData, StartItemData);
		}
	}
	else
	{
		Swap(thisItemData, StartItemData);
	}
}

bool UPlayerInventorySubsystem::CombineItem(EITEMTYPE ItemType ,int8 Index1, int8 Index2)
{
	Inventory Inventory = GetInventory(ItemType);

	TSharedPtr<FItemData>& ItemData1 = (*Inventory)[Index1];
	TSharedPtr<FItemData>& ItemData2 = (*Inventory)[Index2];

	if (ItemData1->Unique_ID == ItemData2->Unique_ID)
	{
		if (ItemData1->CurrentBundleCount == ItemData1->MaxBundleCount)
		{
			return false;
		}
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

TArray<TSharedPtr<FItemData>>* UPlayerInventorySubsystem::GetInventory(EITEMTYPE ItemType)
{
	if (ItemType == EITEMTYPE::GEAR)
	{
		return &GearInventory;
	}
	else
	{
		return &NormalInventory;
	}

}

void UPlayerInventorySubsystem::AttachSlot(ERPGSLOTTYPE SlotType , URPGSlotUserWidget* slot)
{
	switch (SlotType)
	{
	case ERPGSLOTTYPE::NONE:
		break;
	case ERPGSLOTTYPE::INVENTORY_GEAR:
	{
		GearSlots.Add(slot);
		break;
		}
	case ERPGSLOTTYPE::INVENTORY_NORMARL:
	{
		NormalSlots.Add(slot);
		break;
	}
	case ERPGSLOTTYPE::QUICK_ITEM:
	{
		QuickItemSlots.Add(slot);
		break;
	}
	default:
		break;
	}
}

void UPlayerInventorySubsystem::QuickSlotRefresh(int8 QuickSlotIndex)
{

}

URPGSlotUserWidget* UPlayerInventorySubsystem::CheckQuickSlotItem(URPGSlotUserWidget* Slot)
{
	for (int8 i = 0; i < QuickItemSlots.Num(); i++)
	{
		UQuickItemSlotData* data = (UQuickItemSlotData*)QuickItemSlots[i].Get()->GetSlotData();
		if (data->OrginSlot == Slot)
			return QuickItemSlots[i].Get();
	}

	return nullptr;
}



