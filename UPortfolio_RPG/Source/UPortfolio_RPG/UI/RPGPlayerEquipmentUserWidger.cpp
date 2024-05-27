// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RPGPlayerEquipmentUserWidger.h"
#include "GameInstance/RPGGameInstance.h"
#include "Item/PlayerInventorySubsystem.h"
#include "UI/RPGSlot.h"
#include "Components/TextBlock.h"

void URPGPlayerEquipmentUserWidger::Init()
{
	TWeakObjectPtr<UPlayerInventorySubsystem> PlayerInvenSubsytem = GetGameInstance()->GetSubsystem<UPlayerInventorySubsystem>();
	WeaponSlot->SlotIndex = 1;
	HeadSlot->SlotIndex = 2;
	ArmorSlot->SlotIndex = 3;
	PantsSlot->SlotIndex = 4;
	GlovesSlot->SlotIndex =5;
	ShoesSlot->SlotIndex = 6;

}


void URPGPlayerEquipmentUserWidger::RefreshUI()
{	
	WeaponSlot->RefreshSlotUI();
	HeadSlot->RefreshSlotUI();
	ArmorSlot->RefreshSlotUI();
	PantsSlot->RefreshSlotUI();
	GlovesSlot->RefreshSlotUI();
	ShoesSlot->RefreshSlotUI();

	SetAddStat();

}


void URPGPlayerEquipmentUserWidger::ShowInitUI()
{
	RefreshUI();
}

void URPGPlayerEquipmentUserWidger::HideSetUI()
{
}

URPGSlot* URPGPlayerEquipmentUserWidger::GetEquipmentSlot(EGEARTYPE Type)
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

void URPGPlayerEquipmentUserWidger::SetAddStat()
{
	UPlayerInventorySubsystem* Invne = RPGGameInstance->GetPlayerInventorySubsystem();
	int32 AddAtk = Invne->GetEquipmentValue(ESTAT::ATK);
	int32 AddHp = Invne->GetEquipmentValue(ESTAT::HP);
	
	AddHpText->SetText(FText::AsNumber(AddHp));
	AddAtkText->SetText(FText::AsNumber(AddAtk));
}
