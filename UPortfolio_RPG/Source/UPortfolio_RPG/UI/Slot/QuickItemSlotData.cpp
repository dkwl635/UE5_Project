#include "UI/Slot/QuickItemSlotData.h"
#include "UI/Slot/InventorySlotData.h"
#include "UI/RPGQuickSlotUserWidget.h"
#include "Item/ItemEnum.h"
#include "Item/ItemData.h"

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

	if (ItemData.IsValid())
	{
		bValid = false;
	}
	else
	{		
	}
	

	return bValid;
}

UTexture2D* UQuickItemSlotData::GetSlotImg()
{
	if (!IsValid()) { return nullptr; }

	return ItemData.Pin()->ItemImage;

	return nullptr;
	
}

bool UQuickItemSlotData::NormalUse()
{
	if (!IsValid()) { return false; }
	if (!InventorySubsystem.Get()) { return false; }

	InventorySubsystem->UseItem(ItemData.Pin()->ItemType, SlotIndex, 1);



	return true;
}

void UQuickItemSlotData::SetSlotData(UInventorySlotData* Data)
{
	InventoryItemIndex = Data->SlotIndex;
	
}

