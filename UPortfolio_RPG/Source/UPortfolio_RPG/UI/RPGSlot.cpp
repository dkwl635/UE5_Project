// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/RPGSlot.h"
#include "GameInstance/RPGGameInstance.h"
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

 UPlayerInventorySubsystem* URPGSlot::GetInven()
 {
	return RPGGameInstance->GetPlayerInventorySubsystem();
 }

 UDataSubsystem* URPGSlot::GetData()
 {
	 return RPGGameInstance->GetDataSubsyetem();
 }

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
	
		FItemData* Data = GetInven()->GetGearItem(SlotIndex);
		if (Data == nullptr) { return; }
		SlotImg->SetBrushFromTexture(Data->ItemImage);
		if(Data->CurrentBundleCount > 1){ CountText->SetText(FText::AsNumber(Data->CurrentBundleCount)); }
		SlotImg->SetVisibility(ESlateVisibility::Visible);
		
		if (RPGGameInstance->GetUIManager()->isShopOpen) {
			URPGShop* RPGShop = (URPGShop*)RPGGameInstance->GetUIManager()->GetRPGUI(ERPG_UI::SHOP);
			if (RPGShop->CheckSellItem(this)) { SlotImg->SetColorAndOpacity(ShadowColor); }
		}
		return;
	}
	case ERPGSLOTTYPE::INVENTORY_NORMARL:
	{
		Option1 = (int)EITEMTYPE::OTHER;
		FItemData* Data = GetInven()->GetNormalItem(SlotIndex);
		if (Data == nullptr) { return; }
		SlotImg->SetBrushFromTexture(Data->ItemImage);
		if (Data->CurrentBundleCount > 1) { CountText->SetText(FText::AsNumber(Data->CurrentBundleCount)); }
		SlotImg->SetVisibility(ESlateVisibility::Visible);

		if (RPGGameInstance->GetUIManager()->isShopOpen) {
			URPGShop* RPGShop = (URPGShop*)RPGGameInstance->GetUIManager()->GetRPGUI(ERPG_UI::SHOP);
			if (RPGShop->CheckSellItem(this)) { SlotImg->SetColorAndOpacity(ShadowColor); }
		}
		return;
	}
	case ERPGSLOTTYPE::QUICK_ITEM:
	{
		Option1= GetInven()->GetQuickSlotFromIndex(SlotIndex);
		if (Option1 < 0) { 	return; }
		FItemData* Data = GetInven()->GetNormalItem(Option1);
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
		{ Data = GetInven()->GetGearItem(Option1);
		}
		else {
			Data = GetInven()->GetNormalItem(Option1);
		}

		SlotImg->SetBrushFromTexture(Data->ItemImage);
		if (Data->CurrentBundleCount > 1) { CountText->SetText(FText::AsNumber(Data->CurrentBundleCount)); }
		SlotImg->SetVisibility(ESlateVisibility::Visible);
		return;
	}
	case ERPGSLOTTYPE::EQUIPMENT_GEAR:
	{
		FItemData* Data = GetInven()->GetEquipmentItem(SlotIndex);
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
		if (RPGGameInstance->GetUIManager()->isShopOpen) { 
			
			URPGShop* RPGShop = (URPGShop*)RPGGameInstance->GetUIManager()->GetRPGUI(ERPG_UI::SHOP);
			if (RPGShop->CheckSellItem(this)) { break; }

			URPGSlot* SellSlot=	RPGShop->GetEmptySellSlot();
			RPGShop->ShopSwitcher->SetActiveWidgetIndex(1);
			SellSlot->DragEnd(this);
			break;
		}

		FItemData* Data = GetInven()->GetGearItem(SlotIndex);
		EGEARTYPE GearType = GetData()->FindGearData(Data->StatusData.RowName)->EGearType;
		GetInven()->ChangeGear(GearType, SlotIndex);	
		break;
	}
	case ERPGSLOTTYPE::INVENTORY_NORMARL:
	{
		if (RPGGameInstance->GetUIManager()->isShopOpen) {

			URPGShop* RPGShop = (URPGShop*)RPGGameInstance->GetUIManager()->GetRPGUI(ERPG_UI::SHOP);
			if (RPGShop->CheckSellItem(this)) { break; }

			URPGSlot* SellSlot = RPGShop->GetEmptySellSlot();
			RPGShop->ShopSwitcher->SetActiveWidgetIndex(1);
			SellSlot->DragEnd(this);
			break;
		}

		GetInven()->UseItem((EITEMTYPE)Option1, SlotIndex, 1);
		break;
	}
	case ERPGSLOTTYPE::QUICK_ITEM:
	{
		Option1 = GetInven()->GetQuickSlotFromIndex(SlotIndex);
		if (Option1 < 0) { return false ; }
		FItemData* Data = GetInven()->GetNormalItem(Option1);
		if (Data == nullptr) { return false; }
		GetInven()->UseItem(EITEMTYPE::OTHER, Option1, 1);
		break;
	}	
	case ERPGSLOTTYPE::SHOP_SELLITEM:
	{
		ClearSlot();
		RPGGameInstance->GetUIManager()->RefreshUI(ERPG_UI::SHOP);
		RPGGameInstance->GetUIManager()->RefreshUI(ERPG_UI::INVENTORY);
		break;
	}
	case ERPGSLOTTYPE::EQUIPMENT_GEAR:
	{
		GetInven()->DeEquipment((EGEARTYPE)SlotIndex);
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
		GetInven()->SetAttachQuickSlot(SlotIndex, -1);
	}
	case ERPGSLOTTYPE::SHOP_SELLITEM:
	{
		Option1 = -1;
		Option2 = -1;
		Option3 = -1;

		RPGGameInstance->GetUIManager()->RefreshUI(ERPG_UI::SHOP);
		RPGGameInstance->GetUIManager()->RefreshUI(ERPG_UI::INVENTORY);
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
		FItemData* Data = GetInven()->GetGearItem(SlotIndex);
		return Data->ItemName;
	}
	case ERPGSLOTTYPE::INVENTORY_NORMARL:
	{
		FItemData* Data = GetInven()->GetNormalItem(SlotIndex);
		return Data->ItemName;
	}
	case ERPGSLOTTYPE::QUICK_ITEM:
	{
		FItemData* Data = GetInven()->GetNormalItem(Option1);
		return Data->ItemName;
	}
	case ERPGSLOTTYPE::SHOP_SELLITEM:
	{
		FItemData* Data = nullptr;
		if (Option2 == (int)EITEMTYPE::GEAR)
		{
			Data = GetInven()->GetGearItem(Option1);
		}
		else {
			Data = GetInven()->GetNormalItem(Option1);
		}
		return Data->ItemName;
	}		
	case ERPGSLOTTYPE::EQUIPMENT_GEAR:
	{
		FItemData* Data = GetInven()->GetEquipmentItem(SlotIndex);
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
		FItemData* Data = GetInven()->GetGearItem(SlotIndex);
		return Data->ItemDesc;
	}
	case ERPGSLOTTYPE::INVENTORY_NORMARL:
	{
		FItemData* Data = GetInven()->GetNormalItem(SlotIndex);
		return Data->ItemDesc;
	}
	case ERPGSLOTTYPE::QUICK_ITEM:
	{
		FItemData* Data = GetInven()->GetNormalItem(Option1);
		return Data->ItemDesc;
	}
	case ERPGSLOTTYPE::SHOP_SELLITEM:
	{
		FItemData* Data = nullptr;
		if (Option2 == (int)EITEMTYPE::GEAR)
		{
			Data = GetInven()->GetGearItem(Option1);
		}
		else {
			Data = GetInven()->GetNormalItem(Option1);
		}
		return Data->ItemDesc;
	}
	case ERPGSLOTTYPE::EQUIPMENT_GEAR:
	{
		FItemData* Data = GetInven()->GetEquipmentItem(SlotIndex);
		return Data->ItemDesc;
	}
	}

	return	FText();
}

bool URPGSlot::DragEnd(URPGSlot* StartSlot)
{
	if (this == StartSlot) { return true; }

	ERPGSLOTTYPE StartSlotType = StartSlot->RPGSlotType;
	ERPGSLOTTYPE EndSlotType = this->RPGSlotType;

	if ((StartSlotType == ERPGSLOTTYPE::INVENTORY_GEAR && EndSlotType == ERPGSLOTTYPE::INVENTORY_GEAR)
		|| (StartSlotType == ERPGSLOTTYPE::INVENTORY_NORMARL && EndSlotType == ERPGSLOTTYPE::INVENTORY_NORMARL)
		)
	{
		if (RPGGameInstance->GetUIManager()->isShopOpen) { return false; }

		GetInven()->SwapItem((EITEMTYPE)Option1, SlotIndex, StartSlot->SlotIndex);
		this->RefreshSlotUI();
		StartSlot->RefreshSlotUI();
	}
	else if (StartSlotType == ERPGSLOTTYPE::INVENTORY_NORMARL && EndSlotType == ERPGSLOTTYPE::QUICK_ITEM)
	{
		if (RPGGameInstance->GetUIManager()->isShopOpen) { return false; }

		int QuickSlot = GetInven()->CheckQuickSlotItem(StartSlot->SlotIndex);
		if (QuickSlot != -1) { return false; }

		GetInven()->SetAttachQuickSlot(this->SlotIndex, StartSlot->SlotIndex);
		this->RefreshSlotUI();
	}
	else if (StartSlotType == ERPGSLOTTYPE::QUICK_ITEM && EndSlotType == ERPGSLOTTYPE::QUICK_ITEM)
	{
		if (RPGGameInstance->GetUIManager()->isShopOpen) { return false; }

		int temp = this->Option1;
		GetInven()->SetAttachQuickSlot(this->SlotIndex, StartSlot->Option1);
		GetInven()->SetAttachQuickSlot(StartSlot->SlotIndex, temp);

		StartSlot->RefreshSlotUI();
		this->RefreshSlotUI();
	}
	else if ((StartSlotType == ERPGSLOTTYPE::INVENTORY_NORMARL || StartSlotType == ERPGSLOTTYPE::INVENTORY_GEAR)
		&& EndSlotType == ERPGSLOTTYPE::SHOP_SELLITEM)
	{
		URPGShop* RPGShop = (URPGShop*)RPGGameInstance->GetUIManager()->GetRPGUI(ERPG_UI::SHOP);
		if (RPGShop->CheckSellItem(StartSlot)) { return false; }

		this->Option1 = StartSlot->SlotIndex;
		Option2 = StartSlot->Option1;
	
		this->RefreshSlotUI();
		StartSlot->RefreshSlotUI();

		RPGGameInstance->GetUIManager()->RefreshUI(ERPG_UI::SHOP);
		RPGGameInstance->GetUIManager()->RefreshUI(ERPG_UI::INVENTORY);
	}
	else if ((StartSlotType == ERPGSLOTTYPE::INVENTORY_GEAR && EndSlotType == ERPGSLOTTYPE::EQUIPMENT_GEAR)
		|| (StartSlotType == ERPGSLOTTYPE::EQUIPMENT_GEAR && EndSlotType == ERPGSLOTTYPE::INVENTORY_GEAR))
	{
		if (RPGGameInstance->GetUIManager()->isShopOpen) { return false; }
		
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

		FItemData* Data = GetInven()->GetGearItem(InvenSlot->SlotIndex);
		
		EGEARTYPE InvenEqType = EGEARTYPE::None;
		if (Data != nullptr)
		{
			InvenEqType = GetData()->FindGearData(Data->StatusData.RowName)->EGearType;
		}

		EGEARTYPE EqType = (EGEARTYPE)EqSlot->SlotIndex;
		if ((InvenEqType != EGEARTYPE::None) && InvenEqType != EqType) { return false; }
		auto tempData = GetInven()->ChangeGear(EqType, InvenSlot->SlotIndex);
	}
	
	return true;
}

void URPGSlot::DragFailed(URPGSlot* ThisSlot)
{
	ERPGSLOTTYPE StartSlotType = ThisSlot->RPGSlotType;
	switch (StartSlotType)
	{
	case ERPGSLOTTYPE::INVENTORY_GEAR:
	{
		if (RPGGameInstance->GetUIManager()->isShopOpen) { return; }

		RPGGameInstance->GetUIManager()->ShowUI(ERPG_UI::TEXTBOX);
		FOnButtonCallBack YesButtonFunc;
		YesButtonFunc.BindUObject(this, &URPGSlot::RemoveOrginSlotData);
		FOnButtonCallBack NoButtonFunc;
		
		FStringData* data = GetData()->FindStringData(ItemRemoveCheckString);
		FText StringText = data->ItemDesc;
		
		FItemData* Data = GetInven()->GetGearItem(SlotIndex);
		FName ItemName = Data->ItemName;
		FText ItemNameText = FText::FromName(ItemName);

		FText Text = FText::Format(StringText, ItemNameText);
		RPGGameInstance->GetUIManager()->SetYesNoButton(YesButtonFunc, NoButtonFunc, Text);
		break;
	}
	case ERPGSLOTTYPE::INVENTORY_NORMARL:
	{
		if (RPGGameInstance->GetUIManager()->isShopOpen) { return; }

		RPGGameInstance->GetUIManager()->ShowUI(ERPG_UI::TEXTBOX);
		FOnButtonCallBack YesButtonFunc;
		YesButtonFunc.BindUObject(this, &URPGSlot::RemoveOrginSlotData);
		FOnButtonCallBack NoButtonFunc;

		FStringData* data = GetData()->FindStringData(ItemRemoveCheckString);
		FText StringText = data->ItemDesc;

		FItemData* Data = GetInven()->GetNormalItem(SlotIndex);
		FName ItemName = Data->ItemName;
		FText ItemNameText = FText::FromName(ItemName);

		FText Text = FText::Format(StringText, ItemNameText);
		RPGGameInstance->GetUIManager()->SetYesNoButton(YesButtonFunc, NoButtonFunc, Text);
		break;
	}
	case ERPGSLOTTYPE::QUICK_ITEM:
	{
		GetInven()->QuickSlotClear(this->SlotIndex);
		this->RefreshSlotUI();
		break;
	}
	case ERPGSLOTTYPE::EQUIPMENT_GEAR:
	{
		EGEARTYPE GearType = (EGEARTYPE)SlotIndex;
		GetInven()->DeEquipment(GearType);
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
	RPGGameInstance->GetUIManager()->ShowItemBox(mousePos, Data);

}

void URPGSlot::HideItemInfo()
{
	RPGGameInstance->GetUIManager()->HideItemBox();
}

void URPGSlot::RemoveOrginSlotData()
{
	switch (RPGSlotType)
	{
	case ERPGSLOTTYPE::INVENTORY_GEAR:
	{
		GetInven()->RemoveItem(EITEMTYPE::GEAR, SlotIndex, 1);
		ClearSlot();
		break;
	}
	case ERPGSLOTTYPE::INVENTORY_NORMARL:
	{
		GetInven()->RemoveItem(EITEMTYPE::OTHER, SlotIndex, 1);
		ClearSlot();
		break;

	}
	}
}




