// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RPGQuickSlotsUserWidget.h"
#include "GameInstance/RPGGameInstance.h"
#include "Item/PlayerInventorySubsystem.h"
#include "UI/RPGSlot.h"

void URPGQuickSlotsUserWidget::Init()
{
	UPlayerInventorySubsystem* Inven = RPGGameInstance->GetPlayerInventorySubsystem();
	auto Childs =  CanvasPanel->GetSlots();
	
	for (int i = 0; i < Childs.Num(); i++)
	{
		auto content = Childs[i]->Content.Get();
		URPGSlot* SlotWidget = Cast<URPGSlot>(content);
		if (!SlotWidget)
		{
			continue;
		}

		SlotWidget->SlotIndex = i;
		SlotWidget->RefreshSlotUI();
		QuickSlotsIndex.Add(i, SlotWidget);
	}


}

void URPGQuickSlotsUserWidget::RefreshUI()
{
	for (int i = 0; i < QuickSlotsIndex.Num(); i++)
	{
		QuickSlotsIndex[i]->RefreshSlotUI();
	}
}



void URPGQuickSlotsUserWidget::UseQuickSlot(int8 SlotIndex)
{

}
