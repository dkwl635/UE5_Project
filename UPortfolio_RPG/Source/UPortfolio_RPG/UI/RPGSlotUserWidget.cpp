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
	switch (type)
	{

	case 1:
	{
	//	SlotData = MakeShared<UInventorySlotData>(*(new UInventorySlotData()));
		SlotData = NewObject<UInventorySlotData>();

		break;
	}
	case 2:
	{
		SlotData = NewObject<UInventorySlotData>();
		break;
	}
	case 3:
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

void URPGSlotUserWidget::DragEnd(URPGSlotUserWidget* StarDataData)
{

	if (this == StarDataData)
	{
		UE_LOG(LogTemp, Warning, TEXT("Succens DT_ITEM"));
		return;
	}

	ERPGSLOTTYPE StartSlotType = StarDataData->SlotType;
	ERPGSLOTTYPE EndSlotType = this->SlotType;



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

		UPlayerInventorySubsystem* PlayerInven =	GetWorld()->GetGameInstance()->GetSubsystem<UPlayerInventorySubsystem>();

		UInventorySlotData* thisSlotData = (UInventorySlotData*)GetSlotData();
		UInventorySlotData* StartSlotData = (UInventorySlotData*)StarDataData->GetSlotData();

		PlayerInven->SwapItem(ItemType, thisSlotData->SlotIndex, StartSlotData->SlotIndex);
		this->SetSlot();
		StarDataData->SetSlot();
	}
	else if (StartSlotType == ERPGSLOTTYPE::INVENTORY_NORMARL && EndSlotType == ERPGSLOTTYPE::QUICK_ITEM)
	{
		UQuickItemSlotData* thisSlotData = (UQuickItemSlotData*)GetSlotData();
		UInventorySlotData* StartSlotData = (UInventorySlotData*)StarDataData->GetSlotData();
		thisSlotData->SetSlotData(StartSlotData);

	}


	////기타 가방 -> 기타 가방
	//else if ()
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("(StartSlotType == ERPGSLOTTYPE::INVENTORY_NORMARL && EndSlotType == ERPGSLOTTYPE::INVENTORY_NORMARL)"));
	//	
	//	UInventorySlotData* thisSlotData = (UInventorySlotData*)GetSlotData();
	//	UInventorySlotData* StartSlotData = (UInventorySlotData*)StarDataData->GetSlotData();
	//	
	//	TSharedPtr<FItemData>& thisItemData = (*thisSlotData->Inventory)[thisSlotData->ItemIndex];
	//	TSharedPtr<FItemData>& StartItemData = (*StartSlotData->Inventory)[StartSlotData->ItemIndex];
	//		
	//	UE_LOG(LogTemp, Warning, TEXT("thisSlotData %d ,StartSlotData %d") , thisSlotData->ItemIndex , StartSlotData->ItemIndex);


	//	Swap(thisItemData, StartItemData);
	//	thisItemData = nullptr;
	//	StartItemData = nullptr;

	//	TSharedPtr<FItemData>& StartData = S

	//	this->SetSlot();
	//	StarDataData->SetSlot();

	//}
}
