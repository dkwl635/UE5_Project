// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ItemInfoUserWdiget.h"
#include "Item/ItemData.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UItemInfoUserWdiget::ShowItemInfo(ShowBoxData Data)
{
	ImgIcon->SetBrushFromTexture(Data.ItemImage);
	ItmeNameTextBlock->SetText(FText::FromName(Data.ItemName));
	ItemInfoTextBlock->SetText(Data.ItemDesc);
}
