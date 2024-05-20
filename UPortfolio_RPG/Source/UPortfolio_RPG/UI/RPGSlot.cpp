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
#include "Components/WidgetSwitcher.h"
#include "Blueprint/WidgetLayoutLibrary.h"

 FLinearColor ShadowColor = FLinearColor(0.2f, 0.2f, 0.2f);
 FLinearColor OrginColor = FLinearColor(1.0f, 1.0f, 1.0f);

void URPGSlot::RefreshSlotUI()
{
	SlotImg->SetVisibility(ESlateVisibility::Collapsed);
	SlotImg->SetColorAndOpacity(OrginColor);
	CountText->SetText(FText::FromString(TEXT("")));

	switch (RPGSlotType)
	{
	case ERPGSLOTTYPE::INVENTORY_GEAR:
	{
		Option1 = (int)EITEMTYPE::GEAR;
	
		FItemData* Data = UPlayerInventorySubsystem::PlayerInventorySubsystem->GetGearItem(SlotIndex);
		if (Data == nullptr) { return; }
		SlotImg->SetBrushFromTexture(Data->ItemImage);
		if(Data->CurrentBundleCount > 1){ CountText->SetText(FText::AsNumber(Data->CurrentBundleCount)); }
		SlotImg->SetVisibility(ESlateVisibility::Visible);
		
		if (AUIManager::UIManager->isShopOpen) {
			URPGShop* RPGShop = (URPGShop*)AUIManager::UIManager->GetRPGUI(ERPG_UI::SHOP);
			if (RPGShop->CheckSellItem(this)) { SlotImg->SetColorAndOpacity(ShadowColor); }
		}
		return;
	}
	case ERPGSLOTTYPE::INVENTORY_NORMARL:
	{
		Option1 = (int)EITEMTYPE::OTHER;
		FItemData* Data = UPlayerInventorySubsystem::PlayerInventorySubsystem->GetNormalItem(SlotIndex);
		if (Data == nullptr) { return; }
		SlotImg->SetBrushFromTexture(Data->ItemImage);
		if (Data->CurrentBundleCount > 1) { CountText->SetText(FText::AsNumber(Data->CurrentBundleCount)); }
		SlotImg->SetVisibility(ESlateVisibility::Visible);

		if (AUIManager::UIManager->isShopOpen) {
			URPGShop* RPGShop = (URPGShop*)AUIManager::UIManager->GetRPGUI(ERPG_UI::SHOP);
			if (RPGShop->CheckSellItem(this)) { SlotImg->SetColorAndOpacity(ShadowColor); }
		}
		return;
	}
	case ERPGSLOTTYPE::QUICK_ITEM:
	{
		Option1= UPlayerInventorySubsystem::PlayerInventorySubsystem->GetQuickSlotFromIndex(SlotIndex);
		if (Option1 < 0) { 	return; }
		FItemData* Data = UPlayerInventorySubsystem::PlayerInventorySubsystem->GetNormalItem(Option1);
		if (Data == nullptr) {  return; }
		SlotImg->SetBrushFromTexture(Data->ItemImage);
		if (Data->CurrentBundleCount > 1) { CountText->SetText(FText::AsNumber(Data->CurrentBundleCount)); }
		SlotImg->SetVisibility(ESlateVisibility::Visible);
		return;
	}
	case ERPGSLOTTYPE::SHOP_SELLITEM:
	{
		if (Option1 < 0) { return; }
		FItemData* Data = nullptr;
		if (Option2 == (int)EITEMTYPE::GEAR) 
		{ Data = UPlayerInventorySubsystem::PlayerInventorySubsystem->GetGearItem(Option1);
		}
		else {
			Data = UPlayerInventorySubsystem::PlayerInventorySubsystem->GetNormalItem(Option1);
		}

		SlotImg->SetBrushFromTexture(Data->ItemImage);
		if (Data->CurrentBundleCount > 1) { CountText->SetText(FText::AsNumber(Data->CurrentBundleCount)); }
		SlotImg->SetVisibility(ESlateVisibility::Visible);
		return;
	}
	case ERPGSLOTTYPE::EQUIPMENT_GEAR:
	{
		FItemData* Data = UPlayerInventorySubsystem::PlayerInventorySubsystem->GetEquipmentItem(SlotIndex);
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
			RPGShop->ShopSwitcher->SetActiveWidgetIndex(1);
			SellSlot->DragEnd(this);
			break;
		}

		FItemData* Data = UPlayerInventorySubsystem::PlayerInventorySubsystem->GetGearItem(SlotIndex);
		EGEARTYPE GearType = UDataSubsystem::DataSubsystem->FindGearData(Data->StatusData.RowName)->EGearType;
		UPlayerInventorySubsystem::PlayerInventorySubsystem->ChangeGear(GearType, SlotIndex);	
		break;
	}
	case ERPGSLOTTYPE::INVENTORY_NORMARL:
	{
		if (AUIManager::UIManager->isShopOpen) {

			URPGShop* RPGShop = (URPGShop*)AUIManager::UIManager->GetRPGUI(ERPG_UI::SHOP);
			if (RPGShop->CheckSellItem(this)) { break; }

			URPGSlot* SellSlot = RPGShop->GetEmptySellSlot();
			RPGShop->ShopSwitcher->SetActiveWidgetIndex(1);
			SellSlot->DragEnd(this);
			break;
		}

		UPlayerInventorySubsystem::PlayerInventorySubsystem->UseItem((EITEMTYPE)Option1, SlotIndex, 1);
		break;
	}
	case ERPGSLOTTYPE::QUICK_ITEM:
	{
		Option1 = UPlayerInventorySubsystem::PlayerInventorySubsystem->GetQuickSlotFromIndex(SlotIndex);
		if (Option1 < 0) { return false ; }
		FItemData* Data = UPlayerInventorySubsystem::PlayerInventorySubsystem->GetNormalItem(Option1);
		if (Data == nullptr) { return false; }
		UPlayerInventorySubsystem::PlayerInventorySubsystem->UseItem(EITEMTYPE::OTHER, Option1, 1);
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
		UPlayerInventorySubsystem::PlayerInventorySubsystem->DeEquipment((EGEARTYPE)SlotIndex);
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
		UPlayerInventorySubsystem::PlayerInventorySubsystem->SetAttachQuickSlot(SlotIndex, -1);
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
		FItemData* Data = UPlayerInventorySubsystem::PlayerInventorySubsystem->GetGearItem(SlotIndex);
		return Data->ItemName;
	}
	case ERPGSLOTTYPE::INVENTORY_NORMARL:
	{
		FItemData* Data = UPlayerInventorySubsystem::PlayerInventorySubsystem->GetNormalItem(SlotIndex);
		return Data->ItemName;
	}
	case ERPGSLOTTYPE::QUICK_ITEM:
	{
		FItemData* Data = UPlayerInventorySubsystem::PlayerInventorySubsystem->GetNormalItem(Option1);
		return Data->ItemName;
	}
	case ERPGSLOTTYPE::SHOP_SELLITEM:
	{
		FItemData* Data = nullptr;
		if (Option2 == (int)EITEMTYPE::GEAR)
		{
			Data = UPlayerInventorySubsystem::PlayerInventorySubsystem->GetGearItem(Option1);
		}
		else {
			Data = UPlayerInventorySubsystem::PlayerInventorySubsystem->GetNormalItem(Option1);
		}
		return Data->ItemName;
	}		
	case ERPGSLOTTYPE::EQUIPMENT_GEAR:
	{
		FItemData* Data = UPlayerInventorySubsystem::PlayerInventorySubsystem->GetEquipmentItem(SlotIndex);
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
		FItemData* Data = UPlayerInventorySubsystem::PlayerInventorySubsystem->GetGearItem(SlotIndex);
		return Data->ItemDesc;
	}
	case ERPGSLOTTYPE::INVENTORY_NORMARL:
	{
		FItemData* Data = UPlayerInventorySubsystem::PlayerInventorySubsystem->GetNormalItem(SlotIndex);
		return Data->ItemDesc;
	}
	case ERPGSLOTTYPE::QUICK_ITEM:
	{
		FItemData* Data = UPlayerInventorySubsystem::PlayerInventorySubsystem->GetNormalItem(Option1);
		return Data->ItemDesc;
	}
	case ERPGSLOTTYPE::SHOP_SELLITEM:
	{
		FItemData* Data = nullptr;
		if (Option2 == (int)EITEMTYPE::GEAR)
		{
			Data = UPlayerInventorySubsystem::PlayerInventorySubsystem->GetGearItem(Option1);
		}
		else {
			Data = UPlayerInventorySubsystem::PlayerInventorySubsystem->GetNormalItem(Option1);
		}
		return Data->ItemDesc;
	}
	case ERPGSLOTTYPE::EQUIPMENT_GEAR:
	{
		FItemData* Data = UPlayerInventorySubsystem::PlayerInventorySubsystem->GetEquipmentItem(SlotIndex);
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

		UPlayerInventorySubsystem::PlayerInventorySubsystem->SwapItem((EITEMTYPE)Option1, SlotIndex, StartSlot->SlotIndex);
		this->RefreshSlotUI();
		StartSlot->RefreshSlotUI();
	}
	else if (StartSlotType == ERPGSLOTTYPE::INVENTORY_NORMARL && EndSlotType == ERPGSLOTTYPE::QUICK_ITEM)
	{
		if (AUIManager::UIManager->isShopOpen) { return false; }

		int QuickSlot = UPlayerInventorySubsystem::PlayerInventorySubsystem->CheckQuickSlotItem(StartSlot->SlotIndex);
		if (QuickSlot != -1) { return false; }

		UPlayerInventorySubsystem::PlayerInventorySubsystem->SetAttachQuickSlot(this->SlotIndex, StartSlot->SlotIndex);
		this->RefreshSlotUI();
	}
	else if (StartSlotType == ERPGSLOTTYPE::QUICK_ITEM && EndSlotType == ERPGSLOTTYPE::QUICK_ITEM)
	{
		if (AUIManager::UIManager->isShopOpen) { return false; }

		int temp = this->Option1;
		UPlayerInventorySubsystem::PlayerInventorySubsystem->SetAttachQuickSlot(this->SlotIndex, StartSlot->Option1);
		UPlayerInventorySubsystem::PlayerInventorySubsystem->SetAttachQuickSlot(StartSlot->SlotIndex, temp);

		StartSlot->RefreshSlotUI();
		this->RefreshSlotUI();
	}
	else if ((StartSlotType == ERPGSLOTTYPE::INVENTORY_NORMARL || StartSlotType == ERPGSLOTTYPE::INVENTORY_GEAR)
		&& EndSlotType == ERPGSLOTTYPE::SHOP_SELLITEM)
	{
		URPGShop* RPGShop = (URPGShop*)AUIManager::UIManager->GetRPGUI(ERPG_UI::SHOP);
		if (RPGShop->CheckSellItem(StartSlot)) { return false; }

		this->Option1 = StartSlot->SlotIndex;
		Option2 = StartSlot->Option1;
	
		this->RefreshSlotUI();
		StartSlot->RefreshSlotUI();

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

		FItemData* Data = UPlayerInventorySubsystem::PlayerInventorySubsystem->GetGearItem(InvenSlot->SlotIndex);

		EGEARTYPE InvenEqType = UDataSubsystem::DataSubsystem->FindGearData(Data->StatusData.RowName)->EGearType;
		EGEARTYPE EqType = (EGEARTYPE)EqSlot->SlotIndex;
		if (InvenEqType != EqType) { return false; }

		auto tempData = UPlayerInventorySubsystem::PlayerInventorySubsystem->ChangeGear(EqType, InvenSlot->SlotIndex);
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
		UPlayerInventorySubsystem::PlayerInventorySubsystem->QuickSlotClear(this->SlotIndex);
		this->RefreshSlotUI();
		break;
	}
	case ERPGSLOTTYPE::EQUIPMENT_GEAR:
	{
		EGEARTYPE GearType = (EGEARTYPE)SlotIndex;
		UPlayerInventorySubsystem::PlayerInventorySubsystem->DeEquipment(GearType);
		this->RefreshSlotUI();
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

