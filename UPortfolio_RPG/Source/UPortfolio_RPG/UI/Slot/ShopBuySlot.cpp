// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/Slot/ShopBuySlot.h"
#include "UI/RPGSlotUserWidget.h"
#include "Item/ItemData.h"
#include "UI/Slot/ShopSlotData.h"
#include "UI/RPGShop.h"

void UShopBuySlot::Init()
{
	ItemSlot->Init();
	BuySlotData = Cast<UShopSlotData>( ItemSlot->GetSlotData());
	
}
void UShopBuySlot::RefreshUI()
{
	
	ItemSlot->RefreshUI();

	ItemNameText->SetText(FText::FromName( BuyItemInfo->ItemName));
	PriceText->SetText(FText::AsNumber(BuyPrice));
}



void UShopBuySlot::SetShopBuySlot(FItemData* BuyItem,FName RowName,int32 Price, int32 Count)
{
	BuyItemInfo = BuyItem;
	BuySlotData.Get()->SetShopData(BuyItem , Count);
	ItemRowName = RowName;
	BuyPrice = Price;
	BuyCount = Count;

}

void UShopBuySlot::BuyItem()
{
	if (ShopHelper.IsValid())
	{
		ShopHelper.Get()->BuyItem(this);
	}
}