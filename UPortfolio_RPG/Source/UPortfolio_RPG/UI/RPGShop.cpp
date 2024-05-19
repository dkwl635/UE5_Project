// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/RPGShop.h"
#include "Kismet/GameplayStatics.h"
#include "DataSubsystem/DataSubsystem.h"
#include "Components/UniformGridPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "UI/Slot/ShopBuySlot.h"
#include "UI/PlayerUIComponent.h"
#include "UI/RPGMainUserWidget.h"
#include "UI/UIManager.h"
#include "Item/ItemData.h"
#include "Item/PlayerInventorySubsystem.h"
#include "UI/RPGSlot.h"

void URPGShop::Init()
{
	auto SlotList = BuyItemPanel->GetSlots();

	for (int i = 0; i < SlotList.Num(); i++)
	{
		auto content = SlotList[i]->Content.Get();
		UShopBuySlot* ShopSlot = Cast<UShopBuySlot>(content);
		ShopSlot->Init();
		BuyShopSlotList.Add(ShopSlot);
		ShopSlot->ShopHelper = this;
	}

	auto SellSlotList = SellItemList->GetSlots();
	SellSlotMaxCount = SellSlotList.Num();
	for (int i = 0; i < SellSlotList.Num(); i++)
	{
		auto content = SellSlotList[i]->Content.Get();
		URPGSlot* ShopSlot = Cast<URPGSlot>(content);
		ShopSlot->RPGSlotType = ERPGSLOTTYPE::SHOP_SELLITEM;
		ShopSlot->SlotIndex = i;

		ShopSlot->Option1 = -1; //ItmeInventory Index;
		ShopSlot->Option2 = -1;	//ItemType;
		ShopSlot->Option3 = -1;
		SellShopSlotList.Add(ShopSlot);
	}

}

void URPGShop::RefreshUI()
{
	if (ShopSwitcher->GetActiveWidgetIndex() == 0)
	{
		RefreshBuySlot();
		
		FButtonStyle ActivateStyle = BuyButton->GetStyle();
		ActivateStyle.Normal = ActivateButtonStyle;
		ActivateStyle.Hovered = ActivateButtonStyle;
		ActivateStyle.Pressed = ActivateButtonStyle;
		BuyButton->SetStyle(ActivateStyle);

		FButtonStyle  DeactivateStyle = SellButton->GetStyle();
		DeactivateStyle.Normal = DeactivateButtonStyle;
		DeactivateStyle.Hovered = DeactivateButtonStyle;
		DeactivateStyle.Pressed = DeactivateButtonStyle;
		SellButton->SetStyle(DeactivateStyle);

	}
	else if (ShopSwitcher->GetActiveWidgetIndex() == 1)
	{
		RefreshSellSlot();
		SetSellPrice();

		FButtonStyle ActivateStyle = SellButton->GetStyle();
		ActivateStyle.Normal = ActivateButtonStyle;
		ActivateStyle.Hovered = ActivateButtonStyle;
		ActivateStyle.Pressed = ActivateButtonStyle;
		SellButton->SetStyle(ActivateStyle);

		FButtonStyle DeactivateStyle = BuyButton->GetStyle();
		DeactivateStyle.Normal = DeactivateButtonStyle;
		DeactivateStyle.Hovered = DeactivateButtonStyle;
		DeactivateStyle.Pressed = DeactivateButtonStyle;
		BuyButton->SetStyle(DeactivateStyle);
	}
}

void URPGShop::ShowInitUI()
{
	AUIManager::UIManager->isShopOpen = true;

	for (int i = 0; i < SellShopSlotList.Num(); i++)
	{
		auto content = SellShopSlotList[i];
		content->ClearSlot();
	}
	ClearSellPrice();
	ShopSwitcher->SetActiveWidgetIndex(0);
}

void URPGShop::HideSetUI()
{
	AUIManager::UIManager->isShopOpen = false;
}

void URPGShop::SetShopData(TArray<FShopBuyItemData> ShopList)
{
	int SlotCount = BuyShopSlotList.Num();
	for (int i = 0; i < SlotCount; i++)
	{
		UShopBuySlot* ShopSlot = BuyShopSlotList[i].Get();
		if (i >= ShopList.Num())
		{
			ShopSlot->SetVisibility(ESlateVisibility::Collapsed);
			continue;
		}
		else
		{
			FShopBuyItemData Data = ShopList[i];
			FItemData* buyItem = DataSubsystem->FindItem(Data.ItemInfo.RowName);
			int32 Price = Data.Price;
			int32 Count = Data.Count;

			ShopSlot->SetShopBuySlot(buyItem, Data.ItemInfo.RowName,Price, Count);
			ShopSlot->RefreshUI();
		}
	}

}

void URPGShop::BuyItem(UShopBuySlot* ShopSlot)
{
		int32 PlayerCoin = PlayerInventorySubsystem->GetPlayerCoin();
		if (PlayerCoin < ShopSlot->BuyPrice)
		{
			return;
		}
		PlayerCoin -= ShopSlot->BuyPrice;
		PlayerInventorySubsystem->SetPlayerCoin(PlayerCoin);
	
		bool bBuy = PlayerInventorySubsystem->AddItem(ShopSlot->ItemRowName, ShopSlot->BuyCount);

		GetPlayerUI()->GetRPGUI(ERPG_UI::INVENTORY)->RefreshUI();

}

URPGMainUserWidget* URPGShop::GetPlayerUI()
{
	if (!PlayerUI.IsValid())
	{
		auto PlayerControll = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PlayerUI = AUIManager::UIManager->PlayerUI;
	}

	return PlayerUI.Get();

}




bool URPGShop::CheckSellItem(URPGSlot* OrginSlot)
{
	int SellCount = SellShopSlotList.Num();
	for (int i = 0; i < SellCount; i++)
	{
		if (SellShopSlotList[i]->Option1 == OrginSlot ->SlotIndex
			&& SellShopSlotList[i]->Option2 == OrginSlot->Option1)
		{
			return true;
		}
	}

	return false;
}

URPGSlot* URPGShop::GetEmptySellSlot()
{
	int SellCount = SellShopSlotList.Num();
	for (int i = 0; i < SellCount; i++)
	{
		if (SellShopSlotList[i]->Option1 == -1)
		{
			return SellShopSlotList[i].Get();
		}
	}
	return nullptr;

}

void URPGShop::SellItem()
{
	int32 PlayerCurrentCoin = PlayerInventorySubsystem->GetPlayerCoin() + SellItemPrice;
	PlayerInventorySubsystem->SetPlayerCoin(PlayerCurrentCoin);
	
	int SellCount = SellShopSlotList.Num();
	for (int i = 0; i < SellCount; i++)
	{
		if (SellShopSlotList[i]->Option1 >= 0)
		{
			EITEMTYPE ItemType = (EITEMTYPE)SellShopSlotList[i]->Option2;
			PlayerInventorySubsystem->RemoveItem(ItemType, SellShopSlotList[i]->Option1);
			SellShopSlotList[i]->ClearSlot();
			SellShopSlotList[i]->RefreshUI();
		}
	}
	
	GetPlayerUI()->GetRPGUI(ERPG_UI::INVENTORY)->RefreshUI();
	ClearSellPrice();
}

void URPGShop::ClearSellPrice()
{
	SellItemPrice = 0;
	SellPriceText->SetText(FText::AsNumber(SellItemPrice));
}


void URPGShop::SetSellPrice()
{
	int NewPrice = 0;
	int SellCount = SellShopSlotList.Num();
	for (int i = 0; i < SellCount; i++)
	{
		if (SellShopSlotList[i]->IsInValue())
		{
			EITEMTYPE ItemType = (EITEMTYPE)SellShopSlotList[i]->Option2;
			FItemData* Data = nullptr;
			if (ItemType == EITEMTYPE::GEAR)
			{
				Data = PlayerInventorySubsystem->GetGearItem(SellShopSlotList[i]->Option1);
			}
			else
			{
				Data = PlayerInventorySubsystem->GetNormalItem(SellShopSlotList[i]->Option1);
			}
			int ItemCount = Data->CurrentBundleCount;
			int ItemPrice = Data->SellPrice;

			NewPrice += (ItemCount * ItemPrice);
		}
	}
	SellPriceText->SetText(FText::AsNumber(NewPrice));
	SellItemPrice = NewPrice;
}

void URPGShop::RefreshSellSlot()
{
	int SellCount = SellShopSlotList.Num();
	for (int i = 0; i < SellCount; i++)
	{
		SellShopSlotList[i]->RefreshUI();
	}

}

void URPGShop::RefreshBuySlot()
{
	int SlotCount = BuyShopSlotList.Num();
	for (int i = 0; i < SlotCount; i++)
	{
		BuyShopSlotList[i]->RefreshUI();
	}
}


