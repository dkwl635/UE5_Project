// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/RPGSlot.h"
#include "Item/PlayerInventorySubsystem.h"
#include "DataSubsystem/DataSubsystem.h"
#include "UI/UIManager.h"
#include "UI/RPGShop.h"
#include "UI/RPGUserWidget.h"
#include "Item/ItemData.h"
#include "Item/ItemEnum.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void URPGSlot::RefreshUI()
{
	SlotImg->SetVisibility(ESlateVisibility::Collapsed);
	SlotImg->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f));
	CountText->SetText(FText::FromString(TEXT("")));

	switch (RPGSlotType)
	{
	case ERPGSLOTTYPE::INVENTORY_GEAR:
	{
		Option1 = (int)EITEMTYPE::GEAR;
		FItemData* Data = PlayerInventorySubsystem->GetGearItem(SlotIndex);
		if (Data == nullptr) { return; }
		SlotImg->SetBrushFromTexture(Data->ItemImage);
		CountText->SetText(FText::AsNumber(Data->CurrentBundleCount));
		
		SlotImg->SetVisibility(ESlateVisibility::Visible);
		return;
	}
	case ERPGSLOTTYPE::INVENTORY_NORMARL:
	{
		Option1 = (int)EITEMTYPE::OTHER;
		FItemData* Data = PlayerInventorySubsystem->GetNormalItem(SlotIndex);
		if (Data == nullptr) { return; }
		SlotImg->SetBrushFromTexture(Data->ItemImage);
		CountText->SetText(FText::AsNumber(Data->CurrentBundleCount));
		SlotImg->SetVisibility(ESlateVisibility::Visible);

		return;
	}
	case ERPGSLOTTYPE::QUICK_ITEM:
	{
		Option1= PlayerInventorySubsystem->GetQuickSlotFromIndex(SlotIndex);
		if (Option1 < 0) { 	return; }
		FItemData* Data = PlayerInventorySubsystem->GetNormalItem(Option1);
		if (Data == nullptr) {  return; }
		SlotImg->SetBrushFromTexture(Data->ItemImage);
		CountText->SetText(FText::AsNumber(Data->CurrentBundleCount));
		SlotImg->SetVisibility(ESlateVisibility::Visible);
		return;
	}
	case ERPGSLOTTYPE::SHOP_SELLITEM:
	{
		if (Option1 < 0) { return; }
		FItemData* Data = nullptr;
		if (Option2 == (int)EITEMTYPE::GEAR) 
		{ Data = PlayerInventorySubsystem->GetGearItem(Option1);
		}
		else {
			Data = PlayerInventorySubsystem->GetNormalItem(Option1);
		}

		SlotImg->SetBrushFromTexture(Data->ItemImage);
		CountText->SetText(FText::AsNumber(Data->CurrentBundleCount));
		SlotImg->SetVisibility(ESlateVisibility::Visible);
		return;
	}
	case ERPGSLOTTYPE::EQUIPMENT_GEAR:
	{
		FItemData* Data = PlayerInventorySubsystem->GetEquipmentItem(SlotIndex);
		if (Data == nullptr) { return; }
		SlotImg->SetBrushFromTexture(Data->ItemImage);
		CountText->SetText(FText::FromString(TEXT("")));
		SlotImg->SetVisibility(ESlateVisibility::Visible);
		return;
	}
	}

}

bool URPGSlot::UseSlot()
{
	if (SlotImg->GetVisibility() == ESlateVisibility::Collapsed ||
		SlotImg->GetVisibility() == ESlateVisibility::Hidden)
	{
		return false;
	}

	switch (RPGSlotType)
	{
	case ERPGSLOTTYPE::INVENTORY_GEAR:
	{
		if (AUIManager::UIManager->isShopOpen) { 
			
			URPGShop* RPGShop = (URPGShop*)AUIManager::UIManager->GetRPGUI(ERPG_UI::SHOP);
			if (RPGShop->CheckSellItem(this)) { break; }

			URPGSlot* SellSlot=	RPGShop->GetEmptySellSlot();
			SellSlot->DragEnd(this);
			break;
		}

		FItemData* Data = PlayerInventorySubsystem->GetGearItem(SlotIndex);
		EGEARTYPE GearType = DataSubsystem->FindGearData(Data->StatusData.RowName)->EGearType;
		PlayerInventorySubsystem->ChangeGear(GearType, SlotIndex);	
		break;
	}
	case ERPGSLOTTYPE::INVENTORY_NORMARL:
	{
		if (AUIManager::UIManager->isShopOpen) {

			URPGShop* RPGShop = (URPGShop*)AUIManager::UIManager->GetRPGUI(ERPG_UI::SHOP);
			if (RPGShop->CheckSellItem(this)) { break; }

			URPGSlot* SellSlot = RPGShop->GetEmptySellSlot();
			SellSlot->DragEnd(this);
			break;
		}

		PlayerInventorySubsystem->UseItem((EITEMTYPE)Option1, SlotIndex, 1);
		break;
	}
	case ERPGSLOTTYPE::QUICK_ITEM:
	{
		Option1 = PlayerInventorySubsystem->GetQuickSlotFromIndex(SlotIndex);
		if (Option1 < 0) { return false ; }
		FItemData* Data = PlayerInventorySubsystem->GetNormalItem(Option1);
		if (Data == nullptr) { return false; }
		PlayerInventorySubsystem->UseItem(EITEMTYPE::OTHER, Option1, 1);
		break;
	}	
	case ERPGSLOTTYPE::SHOP_SELLITEM:
	{
		ClearSlot();
		AUIManager::UIManager->RefreshUI(ERPG_UI::SHOP);
		AUIManager::UIManager->RefreshUI(ERPG_UI::INVENTORY);
		break;
	}
	case ERPGSLOTTYPE::EQUIPMENT_GEAR:
	{
		PlayerInventorySubsystem->DeEquipment((EGEARTYPE)SlotIndex);
		break;
	}
	}

	return true;

}

bool URPGSlot::IsInValue()
{
	if (!SlotImg) { return false; }

	return SlotImg->GetVisibility() == ESlateVisibility::Visible;
}

void URPGSlot::ClearSlot()
{
	switch (RPGSlotType)
	{
	case ERPGSLOTTYPE::QUICK_ITEM:
	{
		Option1 = -1;
		PlayerInventorySubsystem->SetAttachQuickSlot(SlotIndex, -1);
	}
	case ERPGSLOTTYPE::SHOP_SELLITEM:
	{
		Option1 = -1;
		Option2 = -1;
		Option3 = -1;

		AUIManager::UIManager->RefreshUI(ERPG_UI::SHOP);
		AUIManager::UIManager->RefreshUI(ERPG_UI::INVENTORY);
	}
	}

	//RefreshUI();
}

UTexture2D* URPGSlot::GetSlotImg()
{	
	return (UTexture2D*)SlotImg->GetBrush().GetResourceObject();
}

FName URPGSlot::GetFName()
{
	switch (RPGSlotType)
	{
	case ERPGSLOTTYPE::INVENTORY_GEAR:
	{
		FItemData* Data = PlayerInventorySubsystem->GetGearItem(SlotIndex);
		return Data->ItemName;
	}
	case ERPGSLOTTYPE::INVENTORY_NORMARL:
	{
		FItemData* Data = PlayerInventorySubsystem->GetNormalItem(SlotIndex);
		return Data->ItemName;
	}
	case ERPGSLOTTYPE::QUICK_ITEM:
	{
		FItemData* Data = PlayerInventorySubsystem->GetNormalItem(Option1);
		return Data->ItemName;
	}
	case ERPGSLOTTYPE::SHOP_SELLITEM:
	{
		FItemData* Data = nullptr;
		if (Option2 == (int)EITEMTYPE::GEAR)
		{
			Data = PlayerInventorySubsystem->GetGearItem(Option1);
		}
		else {
			Data = PlayerInventorySubsystem->GetNormalItem(Option1);
		}
		return Data->ItemName;
	}		
	case ERPGSLOTTYPE::EQUIPMENT_GEAR:
	{
		FItemData* Data = PlayerInventorySubsystem->GetEquipmentItem(SlotIndex);
		return Data->ItemName;
	}
	}

	return FName();
}

FText URPGSlot::GetDescFText()
{
	switch (RPGSlotType)
	{
	case ERPGSLOTTYPE::INVENTORY_GEAR:
	{
		FItemData* Data = PlayerInventorySubsystem->GetGearItem(SlotIndex);
		return Data->ItemDesc;
	}
	case ERPGSLOTTYPE::INVENTORY_NORMARL:
	{
		FItemData* Data = PlayerInventorySubsystem->GetNormalItem(SlotIndex);
		return Data->ItemDesc;
	}
	case ERPGSLOTTYPE::QUICK_ITEM:
	{
		FItemData* Data = PlayerInventorySubsystem->GetNormalItem(Option1);
		return Data->ItemDesc;
	}
	case ERPGSLOTTYPE::SHOP_SELLITEM:
	{
		FItemData* Data = nullptr;
		if (Option2 == (int)EITEMTYPE::GEAR)
		{
			Data = PlayerInventorySubsystem->GetGearItem(Option1);
		}
		else {
			Data = PlayerInventorySubsystem->GetNormalItem(Option1);
		}
		return Data->ItemDesc;
	}
	case ERPGSLOTTYPE::EQUIPMENT_GEAR:
	{
		FItemData* Data = PlayerInventorySubsystem->GetEquipmentItem(SlotIndex);
		return Data->ItemDesc;
	}
	}

	return	FText();
}

bool URPGSlot::DragEnd(URPGSlot* StartSlot)
{
	if (this == StartSlot) { return false; }

	ERPGSLOTTYPE StartSlotType = StartSlot->RPGSlotType;
	ERPGSLOTTYPE EndSlotType = this->RPGSlotType;

	if ((StartSlotType == ERPGSLOTTYPE::INVENTORY_GEAR && EndSlotType == ERPGSLOTTYPE::INVENTORY_GEAR)
		|| (StartSlotType == ERPGSLOTTYPE::INVENTORY_NORMARL && EndSlotType == ERPGSLOTTYPE::INVENTORY_NORMARL)
		)
	{
		if (AUIManager::UIManager->isShopOpen) { return false; }

		PlayerInventorySubsystem->SwapItem((EITEMTYPE)Option1, SlotIndex, StartSlot->SlotIndex);
		this->RefreshUI();
		StartSlot->RefreshUI();
	}
	else if (StartSlotType == ERPGSLOTTYPE::INVENTORY_NORMARL && EndSlotType == ERPGSLOTTYPE::QUICK_ITEM)
	{
		if (AUIManager::UIManager->isShopOpen) { return false; }

		int QuickSlot = PlayerInventorySubsystem->CheckQuickSlotItem(StartSlot->SlotIndex);
		if (QuickSlot != -1) { return false; }

		PlayerInventorySubsystem->SetAttachQuickSlot(this->SlotIndex, StartSlot->SlotIndex);
		this->RefreshUI();
	}
	else if (StartSlotType == ERPGSLOTTYPE::QUICK_ITEM && EndSlotType == ERPGSLOTTYPE::QUICK_ITEM)
	{
		if (AUIManager::UIManager->isShopOpen) { return false; }

		int temp = this->Option1;
		PlayerInventorySubsystem->SetAttachQuickSlot(this->SlotIndex, StartSlot->Option1);
		PlayerInventorySubsystem->SetAttachQuickSlot(StartSlot->SlotIndex, temp);

		StartSlot->RefreshUI();
		this->RefreshUI();
	}
	else if ((StartSlotType == ERPGSLOTTYPE::INVENTORY_NORMARL || StartSlotType == ERPGSLOTTYPE::INVENTORY_GEAR)
		&& EndSlotType == ERPGSLOTTYPE::SHOP_SELLITEM)
	{
		URPGShop* RPGShop = (URPGShop*)AUIManager::UIManager->GetRPGUI(ERPG_UI::SHOP);
		if (RPGShop->CheckSellItem(StartSlot)) { return false; }

		this->Option1 = StartSlot->SlotIndex;
		Option2 = StartSlot->Option1;
	
		this->RefreshUI();
		StartSlot->RefreshUI();

		AUIManager::UIManager->RefreshUI(ERPG_UI::SHOP);
		AUIManager::UIManager->RefreshUI(ERPG_UI::INVENTORY);
	}
	else if ((StartSlotType == ERPGSLOTTYPE::INVENTORY_GEAR && EndSlotType == ERPGSLOTTYPE::EQUIPMENT_GEAR)
		|| (StartSlotType == ERPGSLOTTYPE::EQUIPMENT_GEAR && EndSlotType == ERPGSLOTTYPE::INVENTORY_GEAR))
	{
		if (AUIManager::UIManager->isShopOpen) { return false; }
		
		URPGSlot* InvenSlot = nullptr;
		URPGSlot* EqSlot = nullptr;

		if (StartSlotType == ERPGSLOTTYPE::INVENTORY_GEAR)
		{
			InvenSlot = StartSlot;
			EqSlot = this;
		}
		else if (StartSlotType == ERPGSLOTTYPE::EQUIPMENT_GEAR)
		{
			InvenSlot = this;
			EqSlot = StartSlot;
		}

		FItemData* Data = PlayerInventorySubsystem->GetGearItem(InvenSlot->SlotIndex);

		EGEARTYPE InvenEqType = DataSubsystem->FindGearData(Data->StatusData.RowName)->EGearType;
		EGEARTYPE EqType = (EGEARTYPE)EqSlot->SlotIndex;
		if (InvenEqType != EqType) { return false; }

		auto tempData = PlayerInventorySubsystem->ChangeGear(EqType, InvenSlot->SlotIndex);
	}
	
	return true;
}

void URPGSlot::DragFailed(URPGSlot* ThisSlot)
{
	ERPGSLOTTYPE StartSlotType = ThisSlot->RPGSlotType;
	switch (StartSlotType)
	{
	case ERPGSLOTTYPE::INVENTORY_GEAR:
		break;
	case ERPGSLOTTYPE::INVENTORY_NORMARL:
		break;
	case ERPGSLOTTYPE::QUICK_ITEM:
	{
		PlayerInventorySubsystem->QuickSlotClear(this->SlotIndex);
		this->RefreshUI();
		break;
	}
	case ERPGSLOTTYPE::EQUIPMENT_GEAR:
	{
		EGEARTYPE GearType = (EGEARTYPE)SlotIndex;
		PlayerInventorySubsystem->DeEquipment(GearType);
		this->RefreshUI();
		break;
	}
	case ERPGSLOTTYPE::SHOP_SELLITEM:
	{
		this->ClearSlot();
	}
	}

}

void URPGSlot::ShowItemInfo()
{
	if (SlotImg->GetVisibility() == ESlateVisibility::Hidden ||
		SlotImg->GetVisibility() == ESlateVisibility::Collapsed)
	{
		return;
	}

	ShowBoxData Data;
	Data.ItemName = GetFName();
	Data.ItemDesc = GetDescFText();
	Data.ItemImage = GetSlotImg();

	FVector2D mousePos = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	AUIManager::UIManager->ShowItemBox(mousePos, Data);

}

void URPGSlot::HideItemInfo()
{
	AUIManager::UIManager->HideItemBox();
}

