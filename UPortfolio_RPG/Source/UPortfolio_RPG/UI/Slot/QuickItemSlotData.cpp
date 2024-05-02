#include "UI/Slot/QuickItemSlotData.h"
#include "UI/Slot/InventorySlotData.h"

UQuickItemSlotData::UQuickItemSlotData()
{
}

bool UQuickItemSlotData::IsValid()
{
	bool bValid = true;

	if (InventoryItemIndex < 0)
	{
		bValid = false;
	}
	
	if (!Inventory)
	{
		Inventory = InventorySubsystem.Get()->GetInventory(EITEMTYPE::BATTLEITEM);
	}

	InventorySubsystem.Get()->GetItemInfo(Inventory, InventoryItemIndex);

	return bValid;
}

UTexture2D* UQuickItemSlotData::GetSlotImg()
{
	if (!IsValid()) { return nullptr; }

	FItemData* ItemData = (*Inventory)[SlotIndex].Get();
	return ItemData->ItemImage;

	return nullptr;
	
}

bool UQuickItemSlotData::NormalUse()
{
	if (!IsValid()) { return false; }
	if (!InventorySubsystem.Get()) { return false; }

	InventorySubsystem->UseItem(Inventory, SlotIndex, 1);



	return true;
}

void UQuickItemSlotData::SetSlotData(UInventorySlotData* Data)
{
	InventoryItemIndex = Data->ItemIndex;
	
}

