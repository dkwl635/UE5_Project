// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Slot/EquipmentSlotData.h"
#include "UI/RPGSlotUserWidget.h"
#include "Item/ItemData.h"

UEquipmentSlotData::UEquipmentSlotData()
{
	
}

bool UEquipmentSlotData::IsValid()
{
	if (!PlayerInventory)
	{
		return false;
	}

	if (!PlayerInventory->Get())
	{
		return false;
	}


	return  true;
}

void UEquipmentSlotData::SetData()
{
	//TODO
	if (IsValid())
	{
		//	FName RowName = OrginSlot.Get()->GetSlotData()->GetItemData()->StatusData.RowName;
	}
	
}

void UEquipmentSlotData::RefreshData()
{
}

void UEquipmentSlotData::ClearData()
{

	PlayerInventory = nullptr;
	GearData = nullptr;
}

UTexture2D* UEquipmentSlotData::GetSlotImg()
{
	if (!IsValid()) { return nullptr; }

	return PlayerInventory->Get()->ItemImage;
}

int32 UEquipmentSlotData::GetCount()
{
	return 1;
}

bool UEquipmentSlotData::NormalUse()
{
	return false;
}

FItemData* UEquipmentSlotData::GetItemData()
{
	if (!IsValid()) { return nullptr; }

	return PlayerInventory->Get();
}

FGearData* UEquipmentSlotData::GetGearData()
{
	return GearData.Pin().Get();
}
