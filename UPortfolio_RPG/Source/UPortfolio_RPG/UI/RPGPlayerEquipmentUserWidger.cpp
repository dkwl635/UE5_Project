// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RPGPlayerEquipmentUserWidger.h"
#include "UI/Slot/EquipmentSlotData.h"
#include "UI/EquipmentSlot.h"
#include "Item/PlayerInventorySubsystem.h"

void URPGPlayerEquipmentUserWidger::Init()
{
	WeaponSlot->Init();
	HeadSlot->Init();
	ArmorSlot->Init();
	PantsSlot->Init();
	GlovesSlot->Init();
	ShoesSlot->Init();


	TWeakObjectPtr<UPlayerInventorySubsystem> PlayerInvenSubsytem = GetGameInstance()->GetSubsystem<UPlayerInventorySubsystem>();
	UEquipmentSlotData* Data = (UEquipmentSlotData*)WeaponSlot->GetSlotData();
	Data->PlayerInventory = &(PlayerInvenSubsytem.Get()->EquipmentInventory[1]);
	Data = (UEquipmentSlotData*)HeadSlot->GetSlotData();
	Data->PlayerInventory = &(PlayerInvenSubsytem.Get()->EquipmentInventory[2]);
	Data = (UEquipmentSlotData*)ArmorSlot->GetSlotData();
	Data->PlayerInventory = &(PlayerInvenSubsytem.Get()->EquipmentInventory[3]);
	Data = (UEquipmentSlotData*)PantsSlot->GetSlotData();
	Data->PlayerInventory = &(PlayerInvenSubsytem.Get()->EquipmentInventory[4]);
	Data = (UEquipmentSlotData*)GlovesSlot->GetSlotData();
	Data->PlayerInventory = &(PlayerInvenSubsytem.Get()->EquipmentInventory[5]);
	Data = (UEquipmentSlotData*)ShoesSlot->GetSlotData();
	Data->PlayerInventory = &(PlayerInvenSubsytem.Get()->EquipmentInventory[6]);
}


void URPGPlayerEquipmentUserWidger::RefreshUI()
{

	WeaponSlot->RefreshUI();
	HeadSlot->RefreshUI();
	ArmorSlot->RefreshUI();
	PantsSlot->RefreshUI();
	GlovesSlot->RefreshUI();
	ShoesSlot->RefreshUI();
}


void URPGPlayerEquipmentUserWidger::ShowInitUI()
{
	RefreshUI();
}

void URPGPlayerEquipmentUserWidger::HideSetUI()
{
}

UEquipmentSlot* URPGPlayerEquipmentUserWidger::GetEquipmentSlot(EGEARTYPE Type)
{
	switch (Type)
	{
	case EGEARTYPE::WEAPON:
		return WeaponSlot;
	case EGEARTYPE::HEAD:
		return HeadSlot;
	case EGEARTYPE::ARMOR:
		return ArmorSlot;
	case EGEARTYPE::PANTS:
		return PantsSlot;
	case EGEARTYPE::GLOVES:
		return GlovesSlot;
	case EGEARTYPE::SHOES:
		return ShoesSlot;
	default:
		break;
	}
	return nullptr;
}
