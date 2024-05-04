// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Slot/InventorySlotData.h"
#include "Item/PlayerInventorySubsystem.h"
#include "Item/ItemData.h"

UInventorySlotData::UInventorySlotData()
{
}
void UInventorySlotData::SetData()
{
	if (SlotIndex < 0) { return; }
	
	EITEMTYPE itemType = EITEMTYPE::None;
	if (SlotType == ERPGSLOTTYPE::INVENTORY_NORMARL) { itemType = EITEMTYPE::OTHER; }
	else 	if (SlotType == ERPGSLOTTYPE::INVENTORY_GEAR) { itemType = EITEMTYPE::GEAR; }

	ItemData = InventorySubsystem->GetItemInfo(itemType, SlotIndex);
}

void UInventorySlotData::RefreshData()
{
	
	if (!ItemData.IsValid()) 
	{ 
		ClearData();
	}
}

void UInventorySlotData::ClearData()
{
	ItemData = nullptr;

	if (QuickSlot.IsValid())
	{
		QuickSlot->ClearSlot();
		QuickSlot = nullptr;
	}

}

bool UInventorySlotData::IsValid()
{
	bool bValid = true;

	if (SlotIndex < 0) { bValid =  false; }
	if (!ItemData.IsValid()) { bValid =  false; }

	return bValid;
}

UTexture2D* UInventorySlotData::GetSlotImg()
{
	if (!IsValid()) { return nullptr; }
	if (!ItemData.IsValid()) { return nullptr; }

	return ItemData.Pin()->ItemImage;
}

bool UInventorySlotData::NormalUse()
{
	if (!IsValid()) { return false; }
	if (!InventorySubsystem.Get()) { return false; }

	InventorySubsystem->UseItem(ItemData.Pin()->ItemType, SlotIndex, 1);
	
	RefreshData();
	return true;
}

