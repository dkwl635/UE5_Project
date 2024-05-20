// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RPGQuickSlotsUserWidget.h"
#include "Item/PlayerInventorySubsystem.h"
#include "UI/RPGSlot.h"

void URPGQuickSlotsUserWidget::Init()
{
	UPlayerInventorySubsystem* Inven = GetGameInstance()->GetSubsystem<UPlayerInventorySubsystem>();
	auto Childs =  CanvasPanel->GetSlots();
	
	for (int8 i = 0; i < Childs.Num(); i++)
	{
		auto content = Childs[i]->Content.Get();
		URPGSlot* SlotWidget = Cast<URPGSlot>(content);
		if (!SlotWidget)
		{
			continue;
		}

		SlotWidget->SlotIndex = i;
		SlotWidget->RefreshUI();
		QuickSlotsIndex.Add(i, SlotWidget);
	
		UPlayerInventorySubsystem::PlayerInventorySubsystem->AttachSlot(ERPGSLOTTYPE::QUICK_ITEM, SlotWidget);

	}


}

void URPGQuickSlotsUserWidget::RefreshUI()
{
	for (int i = 0; i < QuickSlotsIndex.Num(); i++)
	{
		QuickSlotsIndex[i]->RefreshUI();
	}
}



void URPGQuickSlotsUserWidget::UseQuickSlot(int8 SlotIndex)
{

}
