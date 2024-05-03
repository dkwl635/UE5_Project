// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RPGSlotUserWidget.h"
#include "Slot/InventorySlotData.h"
#include "Slot/QuickItemSlotData.h"
#include "Item/ItemData.h"
#include "Item/PlayerInventorySubsystem.h"



using enum ERPGSLOTTYPE;

void URPGSlotUserWidget::Init()
{

	int type = static_cast<int>(SlotType);
	UE_LOG(LogTemp, Warning, TEXT("Slot : %d"),type);

	switch (SlotType)
	{
	case ERPGSLOTTYPE::NONE:
		break;
	case ERPGSLOTTYPE::INVENTORY_GEAR:
	{
		SlotData = NewObject<UInventorySlotData>();
		break;
	}
	
	case ERPGSLOTTYPE::INVENTORY_NORMARL:
	{
		SlotData = NewObject<UInventorySlotData>();
		break;
	}
	case ERPGSLOTTYPE::QUICK_ITEM:
	{
		SlotData = NewObject<UQuickItemSlotData>();
		break;
	}

	default:
		break;
	}
	

	

	ensure(SlotData);

	SlotData->SlotType = SlotType;

}

URPGSlotUserWidget::~URPGSlotUserWidget()
{
	SlotData = nullptr;
}

void URPGSlotUserWidget::SetSlot()
{
	SlotData->SetData();


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
		SetSlot();
		return true;
	}

	return false;
}





USlotData* URPGSlotUserWidget::GetSlotData()
{
	return SlotData;
}

void URPGSlotUserWidget::DragEnd(URPGSlotUserWidget* StartSlot)
{
	if (this == StartSlot)
	{	
		return;
	}

	ERPGSLOTTYPE StartSlotType = StartSlot->SlotType;
	ERPGSLOTTYPE EndSlotType = this->SlotType;

	UE_LOG(LogTemp, Warning, TEXT("Succens DragEnd"));
	UPlayerInventorySubsystem* PlayerInven = GetWorld()->GetGameInstance()->GetSubsystem<UPlayerInventorySubsystem>();
	//(무기 가방 -> 무기 가방) || (기타 가방 -> 기타 가방)
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
		
		this->SetSlot();
		StartSlot->SetSlot();
	
		if (URPGSlotUserWidget* QuickSlot = PlayerInven->CheckQuickSlotItem(StartSlot))
		{
			UQuickItemSlotData* QuickSlotData = (UQuickItemSlotData*)QuickSlot->GetSlotData();
			QuickSlotData->SetSlotData(this);
			QuickSlot->SetSlot();
		}

	}
	//아이템 창고-> 퀵 슬롯
	else if (StartSlotType == ERPGSLOTTYPE::INVENTORY_NORMARL && EndSlotType == ERPGSLOTTYPE::QUICK_ITEM)
	{
		UE_LOG(LogTemp, Warning, TEXT("ERPGSLOTTYPE::QUICK_ITEM"));
		if (PlayerInven->CheckQuickSlotItem(StartSlot) != nullptr)
		{
			return;
		}

		UQuickItemSlotData* thisSlotData = (UQuickItemSlotData*)GetSlotData();
		UInventorySlotData* StartSlotData = (UInventorySlotData*)StartSlot->GetSlotData();
		thisSlotData->SetSlotData(StartSlot);
		
		this->SetSlot();
	}
	//퀵슬롯 끼리 교환
	else if (StartSlotType == ERPGSLOTTYPE::QUICK_ITEM && EndSlotType == ERPGSLOTTYPE::QUICK_ITEM)
	{
		UE_LOG(LogTemp, Warning, TEXT("QUICK_ITEM && QUICK_ITEM"));
		UQuickItemSlotData* thisSlotData = (UQuickItemSlotData*)GetSlotData();
		UQuickItemSlotData* StartSlotData = (UQuickItemSlotData*)StartSlot->GetSlotData();

		auto temp = thisSlotData->OrginSlot;
		thisSlotData->OrginSlot = StartSlotData->OrginSlot;
		StartSlotData->OrginSlot = temp;
	
		//thisSlotData->SetSlotData(StartSlot);
		StartSlot->SetSlot();
		this->SetSlot();
	}


}
