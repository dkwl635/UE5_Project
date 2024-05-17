// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/Slot/ShopBuySlot.h"
#include "Item/ItemData.h"
#include "UI/RPGShop.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "UI/UIManager.h"
#include "Blueprint/WidgetLayoutLibrary.h"

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

void UShopBuySlot::ShowItemInfo()
{
	if (ItemImage->GetVisibility() == ESlateVisibility::Hidden ||
		ItemImage->GetVisibility() == ESlateVisibility::Collapsed)
	{
		return;
	}

	ShowBoxData Data;
	Data.ItemName = BuyItemInfo->ItemName;
	Data.ItemDesc = BuyItemInfo->ItemDesc;
	Data.ItemImage = BuyItemInfo->ItemImage;

	FVector2D mousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	AUIManager::UIManager->ShowItemBox(mousePos, Data);
}

void UShopBuySlot::HideItemInfo()
{
	AUIManager::UIManager->HideItemBox();
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
