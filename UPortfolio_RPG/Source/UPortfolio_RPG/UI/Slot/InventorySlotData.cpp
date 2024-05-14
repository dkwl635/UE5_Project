// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Slot/InventorySlotData.h"
#include "Item/PlayerInventorySubsystem.h"
#include "Item/ItemData.h"

#include "UI/UIManager.h"
#include "Kismet/GameplayStatics.h"
#include "DataSubsystem/DataSubsystem.h"



UInventorySlotData::UInventorySlotData()
{
}

UPlayerInventorySubsystem* UInventorySlotData::GetInvenSubsystem()
{
	return PlayerInventorySubsystem;
}

bool UInventorySlotData::IsValid()
{
	bool bValid = true;

	if (SlotIndex < 0) { bValid = false; }
	if (!ItemData.IsValid()) { bValid = false; }

	return bValid;
}

void UInventorySlotData::SetData()
{
	if (SlotIndex < 0) { return; }
	
	ItemType = EITEMTYPE::None;
	if (SlotType == ERPGSLOTTYPE::INVENTORY_NORMARL) { ItemType = EITEMTYPE::OTHER; }
	else 	if (SlotType == ERPGSLOTTYPE::INVENTORY_GEAR) { ItemType = EITEMTYPE::GEAR; }

	
	//ItemData = InventorySubsystem->GetItemInfo(ItemType, SlotIndex);
}

int32 UInventorySlotData::GetCount()
{
	if (!ItemData.IsValid()) { return 0; }
	return ItemData.Pin()->CurrentBundleCount;
}

void UInventorySlotData::RefreshData()
{
	ItemData = GetInvenSubsystem()->GetItemInfo(ItemType, SlotIndex);
	if (!ItemData.IsValid()) 
	{ 
		ClearData();
	}
}

void UInventorySlotData::ClearData()
{
	
	ItemData = nullptr;

}



UTexture2D* UInventorySlotData::GetSlotImg()
{
	if (!IsValid()) { return nullptr; }
	if (!ItemData.IsValid()) { return nullptr; }

	return ItemData.Pin()->ItemImage;
}

FItemData* UInventorySlotData::GetItemData()
{
	return ItemData.Pin().Get();
}



bool UInventorySlotData::NormalUse()
{
	if (SlotType == ERPGSLOTTYPE::INVENTORY_GEAR) 
	{ 
		EGEARTYPE GearType = DataSubsystem->FindGearData(ItemData.Pin()->StatusData.RowName)->EGearType;
		GetInvenSubsystem()->ChangeGear(GearType, SlotIndex);
		AUIManager::UIManager->RefreshUI(ERPG_UI::EQUIPMENT);
		return true;
	}
	else
	{
		if (!IsValid()) { return false; }
		if (!GetInvenSubsystem()) { return false; }
		if (AUIManager::UIManager->isShopOpen) { return false; }

		GetInvenSubsystem()->UseItem(ItemData.Pin()->ItemType, SlotIndex, 1);

		RefreshData();
		return true;
	}
	
	return false;
	
}

