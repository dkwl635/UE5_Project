// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Item.h"

UDataSubsystem* UItem::DataSubsystem = nullptr;
TMap<FName, FPotionData*> UItem::PotionDatas;

bool UItem::UseItem(AActor* Target, FItemData* ItemData)
{

	if (!ItemData || !DataSubsystem)
	{
		return false;
	}
	UE_LOG(LogTemp, Warning, TEXT("My Item: %s"), *ItemData->ItemName.ToString());
	if (ItemData->ItemType == EITEMTYPE::POTION)
	{
		FPotionData* PotionData =	GetPotionData(ItemData->StatusData.RowName);
		bool result =  UsePotion(PotionData);
		return result;
	}

	
	return false;
}

FPotionData* UItem::GetPotionData(FName Name)
{

	if (!PotionDatas.Contains(Name))
	{
		FPotionData* GetData = DataSubsystem->FindPotionData(Name);
		UE_LOG(LogTemp, Warning, TEXT("NewItemData: %s"), *Name.ToString());
		PotionDatas.Add(Name, GetData);		
	}

	return PotionDatas[Name];
	
}


bool UItem::UsePotion(FPotionData* PotionData)
{
	if (!PotionData)
	{
		return false;
	}
	UE_LOG(LogTemp, Warning, TEXT("My Name: %d ,: %d"), PotionData->EPotionType , PotionData->PotionValue);

	
	return true;
}
