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

		FButtonStyle ActivateStyle = GearButton->GetStyle();
		ActivateStyle.Normal = ActivateButtonStyle;
		ActivateStyle.Hovered = ActivateButtonStyle;
		ActivateStyle.Pressed = ActivateButtonStyle;
		GearButton->SetStyle(ActivateStyle);

		FButtonStyle  DeactivateStyle = NormalButton->GetStyle();
		DeactivateStyle.Normal = DeactivateButtonStyle;
		DeactivateStyle.Hovered = DeactivateButtonStyle;
		DeactivateStyle.Pressed = DeactivateButtonStyle;
		NormalButton->SetStyle(DeactivateStyle);

	}
	else if (bagIndex == 1)
	{
		NormalInventoryRefresh();
		
		FButtonStyle ActivateStyle = NormalButton->GetStyle();
		ActivateStyle.Normal = ActivateButtonStyle;
		ActivateStyle.Hovered = ActivateButtonStyle;
		ActivateStyle.Pressed = ActivateButtonStyle;
		NormalButton->SetStyle(ActivateStyle);

		FButtonStyle  DeactivateStyle = GearButton->GetStyle();
		DeactivateStyle.Normal = DeactivateButtonStyle;
		DeactivateStyle.Hovered = DeactivateButtonStyle;
		DeactivateStyle.Pressed = DeactivateButtonStyle;
		GearButton->SetStyle(DeactivateStyle);
	}
}

void URPGInventoryUserWidget::GearInventoryRefresh()
{
	int32 Size = GearSlots.Num();
	for (int32 i = 0; i < Size; i++)
	{
		GearSlots[i]->RefreshSlotUI();
	}
}

void URPGInventoryUserWidget::NormalInventoryRefresh()
{
	int32 Size = NormalSlots.Num();
	for (int32 i = 0; i < Size; i++)
	{
		NormalSlots[i]->RefreshSlotUI();
	}
}
