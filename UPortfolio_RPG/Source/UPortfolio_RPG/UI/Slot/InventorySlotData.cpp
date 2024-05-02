// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Slot/InventorySlotData.h"


FInventorySlotData::FInventorySlotData()
{
}

bool FInventorySlotData::IsValid()
{
	if (!Inventory) { return false; }
	if (ItemIndex < 0) { return false; }
	FItemData* ItemData = (*Inventory)[ItemIndex].Get();
	if (!ItemData) { return false; }

	return true;
}

UTexture2D* FInventorySlotData::GetSlotImg()
{
	if (!IsValid()) { return nullptr; }
	
	FItemData* ItemData = (*Inventory)[ItemIndex].Get();
	return ItemData->ItemImage;
}

bool FInventorySlotData::NormalUse()
{
	if (!IsValid()) { return false; }
	if (!World) { return false; }
	World->GetGameInstance()->GetSubsystem<UPlayerInventorySubsystem>()->UseItem(Inventory, ItemIndex, 1);

	return true;
}
