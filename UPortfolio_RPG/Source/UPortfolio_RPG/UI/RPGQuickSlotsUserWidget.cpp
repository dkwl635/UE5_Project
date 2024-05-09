// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RPGQuickSlotsUserWidget.h"
#include "Slot/QuickItemSlotData.h"
#include "Item/PlayerInventorySubsystem.h"
#include "UI/RPGSlotUserWidget.h"

void URPGQuickSlotsUserWidget::Init()
{
	UPlayerInventorySubsystem* Inven = GetGameInstance()->GetSubsystem<UPlayerInventorySubsystem>();
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
		

		SlotWidget->RefreshUI();
		QuickSlotsIndex.Add(i, SlotWidget);
	
	

		Inven->AttachSlot(ERPGSLOTTYPE::QUICK_ITEM, SlotWidget);

	}


}



void URPGQuickSlotsUserWidget::UseQuickSlot(int8 SlotIndex)
{

}
