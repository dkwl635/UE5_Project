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
	CountText->TextDelegate.BindDynamic(this, &ThisClass::GetCountText);
	CountText->SynchronizeProperties();
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
		RefreshSlot();
		return true;
	}

	return false;
}

void URPGSlotUserWidget::ClearSlot()
{
	SlotImg->SetVisibility(ESlateVisibility::Hidden);

	if (SlotType == ERPGSLOTTYPE::INVENTORY_NORMARL)
	{
		UPlayerInventorySubsystem* PlayerInven = GetWorld()->GetGameInstance()->GetSubsystem<UPlayerInventorySubsystem>();
		URPGSlotUserWidget* QuickSlot = PlayerInven->CheckQuickSlotItem(this);
		if (QuickSlot)
		{
			QuickSlot->ClearSlot();
		}
	}

	SlotData->ClearData();
	CountText->SynchronizeProperties();
}

void URPGSlotUserWidget::RefreshSlot()
{	
	//슬롯안에 있는 데이터 갱신

	SlotData->RefreshData();
	CountText->SynchronizeProperties();

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

	UPlayerInventorySubsystem* PlayerInven = GetWorld()->GetGameInstance()->GetSubsystem<UPlayerInventorySubsystem>();
	URPGSlotUserWidget* QuickSlot = PlayerInven->CheckQuickSlotItem(this);
	if (QuickSlot)
	{
		QuickSlot->RefreshSlot();
	}

	
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
	
	
		this->RefreshSlot();
		StartSlot->RefreshSlot();
		

	}
	//아이템 창고-> 퀵 슬롯
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
		this->RefreshSlot();
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
		StartSlot->RefreshSlot();
		this->RefreshSlot();
	}



	return true;
}

void URPGSlotUserWidget::DragFailed(URPGSlotUserWidget* StartSlot)
{
	
	UE_LOG(LogTemp, Warning, TEXT("DragFailed"));

	ERPGSLOTTYPE StartSlotType = StartSlot->SlotType;
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
		this->SetSlot();
		break;
	}		
	default:
		break;
	}

}
