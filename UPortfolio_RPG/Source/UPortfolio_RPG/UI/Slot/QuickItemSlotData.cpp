#include "UI/Slot/QuickItemSlotData.h"
#include "UI/RPGSlotUserWidget.h"

UQuickItemSlotData::UQuickItemSlotData()
{
}

bool UQuickItemSlotData::IsValid()
{
	if (!OrginSlot.Get())
	{
		return false;
	}

	return  true;
}

UTexture2D* UQuickItemSlotData::GetSlotImg()
{
	if (!IsValid()) { return nullptr; }

	return OrginSlot.Get()->GetSlotData()->GetSlotImg();
}

bool UQuickItemSlotData::NormalUse()
{
	if (!IsValid()) { return false; }
	
	OrginSlot.Get()->UseSlot();
	
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
		if (!OrginSlot.Get()->GetSlotData()->IsValid())
		{
			
		}
	}
}


