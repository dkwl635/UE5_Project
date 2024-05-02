// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Slot/InventorySlotData.h"


UInventorySlotData::UInventorySlotData()
{
}

bool UInventorySlotData::IsValid()
{
	bool bValid = true;

	if (!Inventory) { bValid = false; }
	if (SlotIndex < 0) { bValid =  false; }
	FItemData* ItemData = (*Inventory)[SlotIndex].Get();
	if (!ItemData) { bValid =  false; }

	if (!bValid)
	{
		QuickSlotIndex = -1;
	}
	return bValid;
}

UTexture2D* UInventorySlotData::GetSlotImg()
{
	if (!IsValid()) { return nullptr; }
	
	FItemData* ItemData = (*Inventory)[SlotIndex].Get();
	return ItemData->ItemImage;
}

bool UInventorySlotData::NormalUse()
{
	if (!IsValid()) { return false; }
	if (!InventorySubsystem.Get()) { return false; }

	InventorySubsystem->UseItem(Inventory, SlotIndex, 1);
	if (QuickSlotIndex >= 0)
	{
		InventorySubsystem->QuickSlotRefresh(QuickSlotIndex);
	}

	return true;
}
