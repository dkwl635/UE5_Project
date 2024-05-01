// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Slot/InventorySlotData.h"
#include "Item/ItemData.h"

FInventorySlotData::FInventorySlotData()
{
}

UTexture2D* FInventorySlotData::GetSlotImg()
{
	if (!Inventory) { return nullptr; }
	if (ItemIndex < 0 ) { return nullptr; }

	
	FItemData* ItemData = (*Inventory)[ItemIndex].Get();
	if (!ItemData) { return nullptr; }

	return ItemData->ItemImage;
}

bool FInventorySlotData::NormalUse()
{
	if (!Inventory) { return false; }
	if (ItemIndex < 0) { return false; }
	FItemData* ItemData = (*Inventory)[ItemIndex].Get();
	if (!ItemData) { return false; }
	UE_LOG(LogTemp, Warning, TEXT("NormalUse"));
	if (!World) { return false; }
	UE_LOG(LogTemp, Warning, TEXT("World"));
	World->GetGameInstance()->GetSubsystem<UPlayerInventorySubsystem>()->UseItem(Inventory, ItemIndex, 1);

	return true;
}
