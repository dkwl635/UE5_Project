// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/RPGShop.h"
#include "Components/UniformGridPanel.h"
#include "UI/Slot/ShopBuySlot.h"
#include "Components/CanvasPanelSlot.h"
#include "DataSubsystem/DataSubsystem.h"
#include "Item/ItemData.h"

void URPGShop::Init()
{
	auto SlotList = BuyItemPanel->GetSlots();

	for (int i = 0; i < SlotList.Num(); i++)
	{
		auto content = SlotList[i]->Content.Get();
		UShopBuySlot* ShopSlot = Cast<UShopBuySlot>(content);

		ShopSlot->Init();

		BuyShopSlotList.Add(ShopSlot);
	}

}

void URPGShop::RefreshUI()
{

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

			ShopSlot->SetShopBuySlot(buyItem, Price, Count);
			ShopSlot->RefreshUI();
		}



	}

}
