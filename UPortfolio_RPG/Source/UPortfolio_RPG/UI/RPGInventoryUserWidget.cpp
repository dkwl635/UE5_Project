// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/RPGInventoryUserWidget.h"
#include "Item/PlayerInventorySubsystem.h"
#include "Slot/SlotData.h"
#include "Slot/InventorySlotData.h"
#include	"Item/ItemEnum.h"

void URPGInventoryUserWidget::Init()
{
	//return;
	int32 Col = InvenSlotSizeX;
	int32 Row = InvenSlotSizeY;

	UPlayerInventorySubsystem* Inven = GetGameInstance()->GetSubsystem<UPlayerInventorySubsystem>();
	if (!Inven)
	{
		return;
	}	

	auto GearBoxChilds = GearBox->GetSlots();
	for (int8 i = 0; i < GearBoxChilds.Num(); i++)
	{
		auto content = GearBoxChilds[i]->Content.Get();
		URPGSlotUserWidget* SlotWidget = Cast<URPGSlotUserWidget>(content);
		if (!SlotWidget)
		{
			continue;
		}
		SlotWidget->RPGSlotType = ERPGSLOTTYPE::INVENTORY_GEAR;
	
		SlotWidget->Init();
		auto slotData = SlotWidget->GetSlotData();
		if (!slotData)
		{
			UE_LOG(LogTemp, Display, TEXT("slotData null"));
		}
		else
		{
			UInventorySlotData* InvenSlotData = (UInventorySlotData*)slotData;
			InvenSlotData->SlotIndex = i;

			GearSlots.Add(SlotWidget);
			//SlotWidget->RefreshSlot();
		}
	}

	auto NormalBoxChilds = NormalBox->GetSlots();
	for (int8 i = 0; i < NormalBoxChilds.Num(); i++)
	{
		auto content = NormalBoxChilds[i]->Content.Get();
		URPGSlotUserWidget* SlotWidget = Cast<URPGSlotUserWidget>(content);
		if (!SlotWidget)
		{
			continue;
		}
		SlotWidget->RPGSlotType = ERPGSLOTTYPE::INVENTORY_NORMARL;
		SlotWidget->Init();
		auto slotData = SlotWidget->GetSlotData();
		if (!slotData)
		{
			UE_LOG(LogTemp, Display, TEXT("slotData null"));
		}
		else
		{
			UInventorySlotData* InvenSlotData = (UInventorySlotData*)slotData;
			InvenSlotData->SlotIndex = i;

			NormalSlots.Add(SlotWidget);
			//SlotWidget->RefreshSlot();
		}
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
