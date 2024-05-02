// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Slot/InventorySlotData.h"


UInventorySlotData::UInventorySlotData()
{
}

bool UInventorySlotData::IsValid()
{
	if (!Inventory) { return false; }
	if (ItemIndex < 0) { return false; }
	FItemData* ItemData = (*Inventory)[ItemIndex].Get();
	if (!ItemData) { return false; }

	return true;
}

UTexture2D* UInventorySlotData::GetSlotImg()
{
	if (!IsValid()) { return nullptr; }
	
	FItemData* ItemData = (*Inventory)[ItemIndex].Get();
	return ItemData->ItemImage;
}

bool UInventorySlotData::NormalUse()
{
	if (!IsValid()) { return false; }
	if (!World.Get()) { return false; }
	World->GetGameInstance()->GetSubsystem<UPlayerInventorySubsystem>()->UseItem(Inventory, ItemIndex, 1);

	return true;
}
