#include "UI/Slot/QuickItemSlotData.h"
#include "UI/RPGSlotUserWidget.h"
#include "Item/ItemData.h"
#include "Item/PlayerInventorySubsystem.h"

UQuickItemSlotData::UQuickItemSlotData()
{
}

bool UQuickItemSlotData::IsValid()
{
	if (!TempData.IsValid())
	{
		return false;
	}

	return  true;
}

UTexture2D* UQuickItemSlotData::GetSlotImg()
{
	if (!IsValid()) { return nullptr; }

	return TempData.Pin()->ItemImage;
}

bool UQuickItemSlotData::NormalUse()
{
	if (!IsValid()) { return false; }
	
	PlayerInventorySubsystem->UseItem(TempData.Pin()->ItemType , InventoryItemIndex , 1);	
	return true;
}

void UQuickItemSlotData::ClearData()
{
	TempData = nullptr;
	InventoryItemIndex = -1;
}

void UQuickItemSlotData::RefreshData()
{
	InventoryItemIndex = PlayerInventorySubsystem->GetQuickSlotFromIndex(QuickSlotIndex);
	if (InventoryItemIndex != -1)
	{
		TempData = PlayerInventorySubsystem->GetItemInfo(EITEMTYPE::POTION, InventoryItemIndex);
	}
	else
	{
		TempData = nullptr;
	}
	
}

int32 UQuickItemSlotData::GetCount()
{
	if (IsValid())
	{
		return TempData.Pin()->CurrentBundleCount;
	}
	else
	{
		return  0;
	}
	
}

FItemData* UQuickItemSlotData::GetItemData()
{
	return TempData.Pin().Get();
}


