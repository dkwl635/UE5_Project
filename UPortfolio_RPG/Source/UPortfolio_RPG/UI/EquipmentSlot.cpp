// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/EquipmentSlot.h"
#include "UI/Slot/EquipmentSlotData.h"
#include "Item/ItemData.h"

 FGearData* UEquipmentSlot::GetGearData()
{
	 if (IsInValid())
	 {
		UEquipmentSlotData* data =   (UEquipmentSlotData*)GetSlotData();

		if (data)
		{
			return data->GearData;
		}
		
	 }

	 return nullptr;
}
