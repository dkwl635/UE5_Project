// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RPGQuickSlotUserWidget.h"
#include "Slot/QuickItemSlotData.h"

void URPGQuickSlotUserWidget::Init()
{
	auto Childs =  CanvasPanel->GetSlots();
	for (int8 i = 0; i < Childs.Num(); i++)
	{
		auto content = Childs[i]->Content.Get();
		URPGSlotUserWidget* SlotWidget = Cast<URPGSlotUserWidget>(content);
		if (!SlotWidget)
		{
			continue;
		}

		SlotWidget->Init();
		UQuickItemSlotData* data = (UQuickItemSlotData*)SlotWidget->GetSlotData();
		data->Helper = this;
		

		SlotWidget->SetSlot();
		QuickSlotsIndex.Add(i, SlotWidget);
		QuickIndexInvenIndex.Add(i, -1);
	}


}

void URPGQuickSlotUserWidget::SetSlot(URPGSlotUserWidget* InvetorySlotInfo)
{
}

void URPGQuickSlotUserWidget::UseQuickSlot(int8 SlotIndex)
{

}
