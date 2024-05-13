#include "UI/Slot/QuickItemSlotData.h"
#include "UI/RPGSlotUserWidget.h"

UQuickItemSlotData::UQuickItemSlotData()
{
}

bool UQuickItemSlotData::IsValid()
{
	if (!OrginSlot.IsValid())
	{
		return false;
	}

	return  true;
}

UTexture2D* UQuickItemSlotData::GetSlotImg()
{
	if (!IsValid()) { return nullptr; }

	return OrginSlot->GetSlotData()->GetSlotImg();
}

bool UQuickItemSlotData::NormalUse()
{
	if (!IsValid()) { return false; }
	
	OrginSlot->UseSlot();
	
	return true;
}

void UQuickItemSlotData::ClearData()
{
	OrginSlot = nullptr;
}

void UQuickItemSlotData::RefreshData()
{
	if (OrginSlot.IsValid())
	{
		if (!OrginSlot->GetSlotData()->IsValid())
		{
			OrginSlot = nullptr;
		}
	}
}

int32 UQuickItemSlotData::GetCount()
{
	if (OrginSlot->GetSlotData())
	{
		return OrginSlot->GetSlotData()->GetCount();
	}
	else
	{
		return  0;
	}
	
}

FItemData* UQuickItemSlotData::GetItemData()
{
	if (!OrginSlot.IsValid())
	{

		return nullptr;
	}

	return OrginSlot->GetSlotData()->GetItemData();
}


