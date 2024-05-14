// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/RPGShop.h"
#include "Kismet/GameplayStatics.h"
#include "DataSubsystem/DataSubsystem.h"
#include "Components/UniformGridPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "UI/Slot/ShopBuySlot.h"
#include "UI/Slot/Slotdata.h"
#include "UI/Slot/ShopSellSlotData.h"
#include "UI/Slot/InventorySlotData.h"
#include "UI/PlayerUIComponent.h"
#include "UI/RPGMainUserWidget.h"
#include "UI/RPGSlotUserWidget.h"
#include "UI/UIManager.h"
#include "Item/ItemData.h"
#include "Item/PlayerInventorySubsystem.h"

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
		URPGSlotUserWidget* ShopSlot = Cast<URPGSlotUserWidget>(content);
		ShopSlot->Init();

		SellShopSlotDataList.Add(Cast<UShopSellSlotData>(ShopSlot->GetSlotData()));
		SellShopSlotList.Add(ShopSlot);
	}

}

void URPGShop::RefreshUI()
{
	if (ShopSwitcher->GetActiveWidgetIndex() == 0)
	{

	}
	else if (ShopSwitcher->GetActiveWidgetIndex() == 1)
	{
		SetSellPrice();
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
	UDataSubsystem* DataTable = GetGameInstance()->GetSubsystem<UDataSubsystem>();
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
			FItemData* buyItem = DataTable->FindItem(Data.ItemInfo.RowName);
			int32 Price = Data.Price;
			int32 Count = Data.Count;

			ShopSlot->SetShopBuySlot(buyItem, Data.ItemInfo.RowName,Price, Count);
			ShopSlot->RefreshUI();
		}
	}

}

void URPGShop::BuyItem(UShopBuySlot* ShopSlot)
{
		UPlayerInventorySubsystem* PlayerInven = GetGameInstance()->GetSubsystem<UPlayerInventorySubsystem>();

		int32 PlayerCoin = PlayerInven->GetPlayerCoin();
		if (PlayerCoin < ShopSlot->BuyPrice)
		{
			return;
		}
		PlayerCoin -= ShopSlot->BuyPrice;
		PlayerInven->SetPlayerCoin(PlayerCoin);
		
		bool bBuy = PlayerInven->AddItem(ShopSlot->ItemRowName, ShopSlot->BuyCount);

		GetPlayerUI()->GetRPGUI(ERPG_UI::INVENTORY)->RefreshUI();

}

URPGMainUserWidget* URPGShop::GetPlayerUI()
{
	if (!PlayerUI.IsValid())
	{
		auto PlayerControll = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		//	UPlayerUIComponent* Find = (UPlayerUIComponent*)(PlayerControll->GetPawn()->GetComponentByClass(UPlayerUIComponent::StaticClass()));
		//UPlayerUIComponent* Find = PlayerControll->GetPawn()->FindComponentByClass<UPlayerUIComponent>();
		PlayerUI = AUIManager::UIManager->PlayerUI;
	}

	return PlayerUI.Get();

}




bool URPGShop::CheckSellItem(URPGSlotUserWidget* OrginSlot)
{
	int SellCount = SellShopSlotDataList.Num();
	for (int i = 0; i < SellCount; i++)
	{
		if (SellShopSlotDataList[i]->OrginSlot == OrginSlot)
		{
			return false;
		}
	}

	return true;
}

void URPGShop::SellItem()
{
	UPlayerInventorySubsystem* PlayerInven = GetGameInstance()->GetSubsystem<UPlayerInventorySubsystem>();
	
	int32 PlayerCurrentCoin = PlayerInven->GetPlayerCoin() + SellItemPrice;
	PlayerInven->SetPlayerCoin(PlayerCurrentCoin);
	
	int SellCount = SellShopSlotDataList.Num();
	for (int i = 0; i < SellCount; i++)
	{
		if (SellShopSlotDataList[i]->IsValid())
		{
			UInventorySlotData* data = (UInventorySlotData*)SellShopSlotDataList[i]->OrginSlot->GetSlotData();		
			//PlayerInven->RemoveItem(data->ItemData.Pin()->ItemType, data->SlotIndex, SellShopSlotDataList[i]->SellCount);
			PlayerInven->RemoveItem(SellShopSlotDataList[i]->OrginSlot.Get(), 1);
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
	int SellCount = SellShopSlotDataList.Num();
	for (int i = 0; i < SellCount; i++)
	{
		if (SellShopSlotDataList[i]->IsValid())
		{
			UInventorySlotData* data = (UInventorySlotData*)SellShopSlotDataList[i]->OrginSlot->GetSlotData();
			
			if (data->IsValid())
			{
				int ItemCount = data->ItemData.Pin()->CurrentBundleCount;
				int ItemPrice = data->ItemData.Pin()->SellPrice;

				NewPrice += (ItemCount * ItemPrice);
			}
			
		}
	}
	SellPriceText->SetText(FText::AsNumber(NewPrice));
	SellItemPrice = NewPrice;
}


