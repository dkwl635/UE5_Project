// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RPGSlotUserWidget.h"
#include "Slot/InventorySlotData.h"
#include "Slot/QuickItemSlotData.h"
#include "Slot/ShopSlotData.h"
#include "Item/ItemData.h"
#include "Item/PlayerInventorySubsystem.h"
#include "UI/Slot/SlotEnum.h"


void URPGSlotUserWidget::Init()
{
	uint8 type = (uint8)RPGSlotType;
	switch (type)
	{
	case  (uint8)ERPGSLOTTYPE::NONE:
	{
		break;
	}
	case  (uint8)ERPGSLOTTYPE::INVENTORY_GEAR:
	{
		SlotData = NewObject<UInventorySlotData>();
		break;
	}
	
	case  (uint8)ERPGSLOTTYPE::INVENTORY_NORMARL:
	{
		SlotData = NewObject<UInventorySlotData>();
		break;
	}
	case  (uint8)ERPGSLOTTYPE::QUICK_ITEM:
	{
		SlotData = NewObject<UQuickItemSlotData>();
		break;
	}
	case  (uint8)ERPGSLOTTYPE::SHOP_ITEM:
	{
		SlotData = NewObject<UShopSlotData>();
		break;
	}
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
	//���Ծȿ� �ִ� ������ ����
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

	if (RPGSlotType == ERPGSLOTTYPE::INVENTORY_NORMARL)
	{
		UPlayerInventorySubsystem* PlayerInven = GetGameInstance()->GetSubsystem<UPlayerInventorySubsystem>();
		URPGSlotUserWidget* QuickSlot = PlayerInven->CheckQuickSlotItem(this);
		if (QuickSlot)
		{
			QuickSlot->RefreshUI();
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
		UPlayerInventorySubsystem* PlayerInven = GetGameInstance()->GetSubsystem<UPlayerInventorySubsystem>();
		URPGSlotUserWidget* QuickSlot = PlayerInven->CheckQuickSlotItem(this);
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
	UPlayerInventorySubsystem* PlayerInven = GetGameInstance()->GetSubsystem<UPlayerInventorySubsystem>();
	//(���� ���� -> ���� ����) || (��Ÿ ���� -> ��Ÿ ����)
	if ((StartSlotType == ERPGSLOTTYPE::INVENTORY_GEAR && EndSlotType == ERPGSLOTTYPE::INVENTORY_GEAR)
		|| (StartSlotType == ERPGSLOTTYPE::INVENTORY_NORMARL && EndSlotType == ERPGSLOTTYPE::INVENTORY_NORMARL)
		)
	{
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
			
		}
		else if (QuickSlot1)
		{
			UQuickItemSlotData* QuickSlotData1 = (UQuickItemSlotData*)QuickSlot1->GetSlotData();
			QuickSlotData1->OrginSlot = this;
		}
	
	
		this->RefreshUI();
		StartSlot->RefreshUI();
		

	}
	//������ â��-> �� ����
	else if (StartSlotType == ERPGSLOTTYPE::INVENTORY_NORMARL && EndSlotType == ERPGSLOTTYPE::QUICK_ITEM)
	{
		UE_LOG(LogTemp, Warning, TEXT("ERPGSLOTTYPE::QUICK_ITEM"));
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
	//������ ���� ��ȯ
	else if (StartSlotType == ERPGSLOTTYPE::QUICK_ITEM && EndSlotType == ERPGSLOTTYPE::QUICK_ITEM)
	{
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
