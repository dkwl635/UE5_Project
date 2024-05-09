// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/Slot/ShopSlotData.h"
#include "Item/ItemData.h"


void UShopSlotData::SetShopData(FItemData* NewData, int32 Count)
{
	ItemData = NewData;
	BuyCount = Count;
}

int32 UShopSlotData::GetCount()
{
	return BuyCount;
}

bool UShopSlotData::IsValid()
{
	return true;
}

void UShopSlotData::ClearData()
{
}

UTexture2D* UShopSlotData::GetSlotImg()
{
	return ItemData->ItemImage;
}
