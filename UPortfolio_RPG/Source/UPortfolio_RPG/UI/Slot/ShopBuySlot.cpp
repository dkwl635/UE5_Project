// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/Slot/ShopBuySlot.h"
#include "Item/ItemData.h"
#include "UI/RPGShop.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UShopBuySlot::Init()
{
	
}
void UShopBuySlot::RefreshUI()
{
	if (BuyItemInfo)
	{
		ItemImage->SetBrushFromTexture(BuyItemInfo->ItemImage);
		ItemCount->SetText(FText::AsNumber(BuyCount));
		ItemNameText->SetText(FText::FromName(BuyItemInfo->ItemName));
		PriceText->SetText(FText::AsNumber(BuyPrice));
	}
}

void UShopBuySlot::SetShopBuySlot(FItemData* BuyItem,FName RowName,int32 Price, int32 Count)
{
	BuyItemInfo = BuyItem;
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
