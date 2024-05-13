// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RPGSlotUserWidget.h"
#include "UI/EquipmentSlot.h"
#include "Slot/InventorySlotData.h"
#include "Slot/QuickItemSlotData.h"
#include "Slot/ShopSlotData.h"
#include "Slot/ShopSellSlotData.h"
#include "Slot/EquipmentSlotData.h"
#include "Item/ItemData.h"
#include "Item/ItemEnum.h"
#include "Item/PlayerInventorySubsystem.h"
#include "UI/Slot/SlotEnum.h"
#include "UI/UIManager.h"
#include "UI/RPGShop.h"
#include "UI/RPGMainUserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"


void URPGSlotUserWidget::Init()
{
	uint8 type = (uint8)RPGSlotType;
	switch (type)
	{
	case  (uint8)ERPGSLOTTYPE::NONE: { break; }
	case  (uint8)ERPGSLOTTYPE::INVENTORY_GEAR:
	{ SlotData = NewObject<UInventorySlotData>(); break; }
	case  (uint8)ERPGSLOTTYPE::INVENTORY_NORMARL:
	{ SlotData = NewObject<UInventorySlotData>(); break; }
	case  (uint8)ERPGSLOTTYPE::QUICK_ITEM:
	{ SlotData = NewObject<UQuickItemSlotData>(); break; }
	case  (uint8)ERPGSLOTTYPE::SHOP_ITEM:
	{ SlotData = NewObject<UShopSlotData>();	break; }
	case  (uint8)ERPGSLOTTYPE::SHOP_SELLITEM:
	{ SlotData = NewObject<UShopSellSlotData>(); break; }
	case  (uint8)ERPGSLOTTYPE::EQUIPMENT_GEAR:
	{ SlotData = NewObject<UEquipmentSlotData>(); break; }
	default:
		break;
	}
	
	ensure(SlotData);

	SlotData->SlotType = RPGSlotType;
	SlotData->SetData();
	CountText->TextDelegate.BindDynamic(this, &ThisClass::GetCountText);
	CountText->SynchronizeProperties();
}

URPGSlotUserWidget::~URPGSlotUserWidget()
{
	SlotData = nullptr;
}



void URPGSlotUserWidget::RefreshUI()
{
	//슬롯안에 있는 데이터 갱신
	SlotData->RefreshData();
	CountText->SynchronizeProperties();

	bool test = SlotData->IsValid();
	if (!SlotData->IsValid())
	{
		ClearSlot();
		return;
	}

	UTexture2D* newImg = SlotData->GetSlotImg();
	if (!newImg)
	{
		SlotImg->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		SlotImg->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		SlotImg->SetBrushFromTexture(newImg);
	}
	SlotImg->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f));


	if (RPGSlotType == ERPGSLOTTYPE::INVENTORY_NORMARL)
	{
		//UPlayerInventorySubsystem* PlayerInven = GetGameInstance()->GetSubsystem<UPlayerInventorySubsystem>();
		URPGSlotUserWidget* QuickSlot = GetPlayerInvenSubsytem()->CheckQuickSlotItem(this);
		if (QuickSlot)
		{
			QuickSlot->RefreshUI();
		}
	}

	if (AUIManager::UIManager->isShopOpen)
	{
		URPGShop* RPGShop = (URPGShop*)AUIManager::UIManager->PlayerUI->GetRPGUI(ERPG_UI::SHOP);
		if (!RPGShop->CheckSellItem(this))
		{
			//Saturation
			//ColorAndOpacity
			SlotImg->SetColorAndOpacity(FLinearColor(0.2f,0.2f,0.2f));

		}
		else
		{
			SlotImg->SetColorAndOpacity(FLinearColor(1.0f, 1.0f, 1.0f));
		}
	}


}

bool URPGSlotUserWidget::IsInValid()
{
	if (!GetSlotData()) { return false; }
	return GetSlotData()->IsValid();

}

bool URPGSlotUserWidget::UseSlot()
{
	if (!SlotData) { return false; }

	if (SlotData->NormalUse())
	{
		RefreshUI();
		return true;
	}

	return false;
}

void URPGSlotUserWidget::ClearSlot()
{
	SlotImg->SetVisibility(ESlateVisibility::Collapsed);

	if (RPGSlotType == ERPGSLOTTYPE::INVENTORY_NORMARL)
	{
		//UPlayerInventorySubsystem* PlayerInven = GetGameInstance()->GetSubsystem<UPlayerInventorySubsystem>();
		URPGSlotUserWidget* QuickSlot = GetPlayerInvenSubsytem()->CheckQuickSlotItem(this);
		if (QuickSlot)
		{
			QuickSlot->ClearSlot();
		}
	}

	SlotData->ClearData();
	CountText->SynchronizeProperties();
}


FText URPGSlotUserWidget::GetCountText()
{

	if (!SlotData->IsValid())
	{
		FText text = FText::FromString(TEXT(""));
		return text;
	}
	else
	{
		int32 Count = SlotData->GetCount();
		if (Count == 1)
		{
			FText text = FText::FromString(TEXT(""));
			return text;
		}

		FText text = FText::AsNumber(Count);
		return text;
	}
}




TWeakObjectPtr<UPlayerInventorySubsystem> URPGSlotUserWidget::GetPlayerInvenSubsytem()
{
	//static 	TWeakObjectPtr<UPlayerInventorySubsystem> PlayerInvenSubsytem;
	//if (!PlayerInvenSubsytem.IsValid())
	//{
	//	PlayerInvenSubsytem = GetGameInstance()->GetSubsystem<UPlayerInventorySubsystem>();
	//}
	TWeakObjectPtr<UPlayerInventorySubsystem> PlayerInvenSubsytem = GetGameInstance()->GetSubsystem<UPlayerInventorySubsystem>();
	return PlayerInvenSubsytem;
}

USlotData* URPGSlotUserWidget::GetSlotData()
{
	return SlotData;
}

bool URPGSlotUserWidget::DragEnd(URPGSlotUserWidget* StartSlot)
{
	if (this == StartSlot)
	{	
		return false;
	}

	ERPGSLOTTYPE StartSlotType = StartSlot->RPGSlotType;
	ERPGSLOTTYPE EndSlotType = this->RPGSlotType;

	UE_LOG(LogTemp, Warning, TEXT("Succens DragEnd"));
	UPlayerInventorySubsystem* PlayerInven = GetPlayerInvenSubsytem().Get();
	//(무기 가방 -> 무기 가방) || (기타 가방 -> 기타 가방)
	if ((StartSlotType == ERPGSLOTTYPE::INVENTORY_GEAR && EndSlotType == ERPGSLOTTYPE::INVENTORY_GEAR)
		|| (StartSlotType == ERPGSLOTTYPE::INVENTORY_NORMARL && EndSlotType == ERPGSLOTTYPE::INVENTORY_NORMARL)
		)
	{
		if (AUIManager::UIManager->isShopOpen)
		{
			return false;
		}

		EITEMTYPE ItemType = EITEMTYPE::None;
		if (StartSlotType == ERPGSLOTTYPE::INVENTORY_GEAR)
		{
			ItemType = EITEMTYPE::GEAR;
		}
		else if (StartSlotType == ERPGSLOTTYPE::INVENTORY_NORMARL)
		{
			ItemType = EITEMTYPE::OTHER;
		}

		UInventorySlotData* ThisSlotData = (UInventorySlotData*)GetSlotData();
		UInventorySlotData* StartSlotData = (UInventorySlotData*)StartSlot->GetSlotData();

		PlayerInven->SwapItem(ItemType, ThisSlotData->SlotIndex, StartSlotData->SlotIndex);		

		URPGSlotUserWidget* QuickSlot1 = PlayerInven->CheckQuickSlotItem(StartSlot);
		URPGSlotUserWidget* QuickSlot2 = PlayerInven->CheckQuickSlotItem(this);
		if (QuickSlot1 && QuickSlot2)
		{
			UQuickItemSlotData* QuickSlotData1 = (UQuickItemSlotData*)QuickSlot1->GetSlotData();	
			UQuickItemSlotData* QuickSlotData2 = (UQuickItemSlotData*)QuickSlot2->GetSlotData();
			Swap(QuickSlotData1->OrginSlot , QuickSlotData2->OrginSlot);
			QuickSlot1->RefreshUI();
			QuickSlot2->RefreshUI();
			
		}
		else if (QuickSlot1)
		{
			UQuickItemSlotData* QuickSlotData1 = (UQuickItemSlotData*)QuickSlot1->GetSlotData();
			ThisSlotData->RefreshData();
			StartSlotData->RefreshData();
			QuickSlotData1->OrginSlot = this;
			QuickSlot1->RefreshUI();
		}
	
	
		this->RefreshUI();
		StartSlot->RefreshUI();
		

	}
	//아이템 창고-> 퀵 슬롯
	else if (StartSlotType == ERPGSLOTTYPE::INVENTORY_NORMARL && EndSlotType == ERPGSLOTTYPE::QUICK_ITEM)
	{
		if (AUIManager::UIManager->isShopOpen)
		{
			return false;
		}

		
		URPGSlotUserWidget* QuickSlot = PlayerInven->CheckQuickSlotItem(StartSlot);
		if (QuickSlot != nullptr)
		{
			return false;
		}

		UQuickItemSlotData* thisSlotData = (UQuickItemSlotData*)GetSlotData();
		UInventorySlotData* StartSlotData = (UInventorySlotData*)StartSlot->GetSlotData();
		thisSlotData->OrginSlot = StartSlot;
		//StartSlotData->QuickSlot = this;
		this->RefreshUI();
	}
	//퀵슬롯 끼리 교환
	else if (StartSlotType == ERPGSLOTTYPE::QUICK_ITEM && EndSlotType == ERPGSLOTTYPE::QUICK_ITEM)
	{
		if (AUIManager::UIManager->isShopOpen)
		{
			return false;
		}

		UE_LOG(LogTemp, Warning, TEXT("QUICK_ITEM && QUICK_ITEM"));
		UQuickItemSlotData* thisSlotData = (UQuickItemSlotData*)GetSlotData();
		UQuickItemSlotData* StartSlotData = (UQuickItemSlotData*)StartSlot->GetSlotData();

		auto temp = thisSlotData->OrginSlot;
		thisSlotData->OrginSlot = StartSlotData->OrginSlot;
		StartSlotData->OrginSlot = temp;
	

		//thisSlotData->SetSlotData(StartSlot);
		StartSlot->RefreshUI();
		this->RefreshUI();
	}
	else if ((StartSlotType == ERPGSLOTTYPE::INVENTORY_NORMARL || StartSlotType == ERPGSLOTTYPE::INVENTORY_GEAR)
		&& EndSlotType == ERPGSLOTTYPE::SHOP_SELLITEM)
	{
		UE_LOG(LogTemp, Warning, TEXT("ERPGSLOTTYPE::SHOP_SELLITEM"));

		URPGShop* RPGShop = (URPGShop*)AUIManager::UIManager->PlayerUI->GetRPGUI(ERPG_UI::SHOP);
		if (!RPGShop->CheckSellItem(StartSlot))
		{
			return false;
		}
		UShopSellSlotData* thisSlotData = (UShopSellSlotData*)GetSlotData();
		UInventorySlotData* StartSlotData = (UInventorySlotData*)StartSlot->GetSlotData();
		thisSlotData->OrginSlot = StartSlot;
		//StartSlotData->QuickSlot = this;
		this->RefreshUI();
		StartSlot->RefreshUI();

	}
	else if (StartSlotType == ERPGSLOTTYPE::INVENTORY_GEAR && EndSlotType == ERPGSLOTTYPE::EQUIPMENT_GEAR)
	{
		if (AUIManager::UIManager->isShopOpen)
		{
			return false;
		}

		UInventorySlotData* StartSlotData = (UInventorySlotData*)StartSlot->GetSlotData();
		//FItemData* StartItemData = 

		UEquipmentSlot* EqSlot = (UEquipmentSlot*)this;

		EGEARTYPE StartType = EGEARTYPE::WEAPON;
		EGEARTYPE EndType = EqSlot->EGearType;

		if (StartType != EndType){return false;}

		auto tempData = PlayerInven->ChangeGear(StartType, StartSlotData->SlotIndex);

		
		StartSlot->RefreshUI();
		this->RefreshUI();
	}

	return true;
}

void URPGSlotUserWidget::DragFailed(URPGSlotUserWidget* StartSlot)
{
	UE_LOG(LogTemp, Warning, TEXT("DragFailed"));

	ERPGSLOTTYPE StartSlotType = StartSlot->RPGSlotType;
	switch (StartSlotType)
	{
	case ERPGSLOTTYPE::NONE:
		break;
	case ERPGSLOTTYPE::INVENTORY_GEAR:
		break;
	case ERPGSLOTTYPE::INVENTORY_NORMARL:
		break;
	case ERPGSLOTTYPE::QUICK_ITEM:
	{
		UQuickItemSlotData* StartSlotData = (UQuickItemSlotData*)StartSlot->GetSlotData();
		StartSlotData->OrginSlot = nullptr;
		this->RefreshUI();
		break;
	}		
	default:
		break;
	}

}

void URPGSlotUserWidget::ShowItemInfo()
{
	if (!SlotData->IsValid())
	{
		return;
	}

	FItemData* Data = SlotData->GetItemData();
	if (!Data)
	{
		return;
	}
	
	FVector2D mousePos =	UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	AUIManager::UIManager->ShowItemBox(mousePos,  Data);

}

void URPGSlotUserWidget::HideItemInfo()
{
	AUIManager::UIManager->HideItemBox();
}
