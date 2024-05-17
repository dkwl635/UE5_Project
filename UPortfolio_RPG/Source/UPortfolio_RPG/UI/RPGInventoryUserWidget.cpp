// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/RPGInventoryUserWidget.h"
#include "UI/RPGSlot.h"
#include "Item/PlayerInventorySubsystem.h"
#include "Item/ItemEnum.h"

void URPGInventoryUserWidget::Init()
{
	//return;
	int32 Col = InvenSlotSizeX;
	int32 Row = InvenSlotSizeY;

	auto GearBoxChilds = GearBox->GetSlots();
	for (int8 i = 0; i < GearBoxChilds.Num(); i++)
	{
		auto content = GearBoxChilds[i]->Content.Get();
		URPGSlot* SlotWidget = Cast<URPGSlot>(content);
		if (!SlotWidget)
		{
			continue;
		}
		SlotWidget->RPGSlotType = ERPGSLOTTYPE::INVENTORY_GEAR;
		SlotWidget->SlotIndex = i;
		GearSlots.Add(SlotWidget);
	}
	auto NormalBoxChilds = NormalBox->GetSlots();
	for (int8 i = 0; i < NormalBoxChilds.Num(); i++)
	{
		auto content = NormalBoxChilds[i]->Content.Get();
		URPGSlot* SlotWidget = Cast<URPGSlot>(content);
		if (!SlotWidget)
		{
			continue;
		}
		SlotWidget->RPGSlotType = ERPGSLOTTYPE::INVENTORY_NORMARL;
		SlotWidget->SlotIndex = i;
		NormalSlots.Add(SlotWidget);
	}
	
}

void URPGInventoryUserWidget::RefreshUI()
{
	int bagIndex = BagWidgetSwitcher->GetActiveWidgetIndex();
	if (bagIndex == 0)
	{
		GearInventoryRefresh();
	}
	else if (bagIndex == 1)
	{
		NormalInventoryRefresh();
	}
}

void URPGInventoryUserWidget::GearInventoryRefresh()
{
	int32 Size = GearSlots.Num();
	for (int32 i = 0; i < Size; i++)
	{
		GearSlots[i]->RefreshUI();
	}
}

void URPGInventoryUserWidget::NormalInventoryRefresh()
{
	int32 Size = NormalSlots.Num();
	for (int32 i = 0; i < Size; i++)
	{
		NormalSlots[i]->RefreshUI();
	}
}
