// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/Slot/ShopSellSlotData.h"
#include "UI/RPGSlotUserWidget.h"
#include "UI/UIManager.h"
#include "UI/RPGMainUserWidget.h"
#include "UI/RPGShop.h"

int32 UShopSellSlotData::GetCount()
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

bool UShopSellSlotData::IsValid()
{
	if (!OrginSlot.IsValid())
	{
		return false;
	}

	return  true;
}

void UShopSellSlotData::ClearData()
{
	OrginSlot = nullptr;
}

UTexture2D* UShopSellSlotData::GetSlotImg()
{
	if (!IsValid()) { return nullptr; }

	return OrginSlot->GetSlotData()->GetSlotImg();
}

void UShopSellSlotData::RefreshData()
{
	auto UI = AUIManager::UIManager->PlayerUI->GetRPGUI(ERPG_UI::SHOP);
	UI->RefreshUI();
}


bool UShopSellSlotData::NormalUse()
{
	ClearData();

	auto UI =  AUIManager::UIManager->PlayerUI->GetRPGUI(ERPG_UI::SHOP);
	UI->RefreshUI();

	return true;

}
