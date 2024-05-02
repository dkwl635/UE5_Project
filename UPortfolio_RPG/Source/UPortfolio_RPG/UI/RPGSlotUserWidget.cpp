// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RPGSlotUserWidget.h"
#include "Slot/SlotData.h"
#include "Slot/InventorySlotData.h"

UUserWidget* URPGSlotUserWidget::DragUserWidgetPonter = nullptr;

void URPGSlotUserWidget::InitSlot()
{

	switch (SlotType)
	{
	case ERPGSLOTTYPE::NONE:
		break;
	case ERPGSLOTTYPE::INVENTORY_GEAR:
	{
	//	SlotData = MakeShared<UInventorySlotData>(*(new UInventorySlotData()));
		SlotData = NewObject<UInventorySlotData>();

		break;
	}
	case ERPGSLOTTYPE::INVENTORY_NORMARL:
	{
		SlotData = NewObject<UInventorySlotData>();
		break;
	}
	default:
		break;
	}

	if (DragUserWidgetPonter == nullptr)
	{
		DragUserWidgetPonter = CreateWidget(GetWorld(), DragUserWidget);
	}


	
}

URPGSlotUserWidget::~URPGSlotUserWidget()
{
	SlotData = nullptr;

	int a = 1;

	
}

void URPGSlotUserWidget::SetSlot()
{


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



UUserWidget* URPGSlotUserWidget::GetDragUserWidget()
{
	return DragUserWidgetPonter;
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

	//무기 가방 -> 무기 가방
	if (StartSlotType == ERPGSLOTTYPE::INVENTORY_GEAR && EndSlotType == ERPGSLOTTYPE::INVENTORY_GEAR)
	{

	}
	//기타 가방 -> 기타 가방
	else if (StartSlotType == ERPGSLOTTYPE::INVENTORY_NORMARL && EndSlotType == ERPGSLOTTYPE::INVENTORY_NORMARL)
	{
		//UE_LOG(LogTemp, Warning, TEXT("(StartSlotType == ERPGSLOTTYPE::INVENTORY_NORMARL && EndSlotType == ERPGSLOTTYPE::INVENTORY_NORMARL)"));
		
		UInventorySlotData* thisSlotData = (UInventorySlotData*)GetSlotData();
		UInventorySlotData* StartSlotData = (UInventorySlotData*)StarDataData->GetSlotData();
		
		TSharedPtr<FItemData>& thisItemData = (*thisSlotData->Inventory)[thisSlotData->ItemIndex];
		TSharedPtr<FItemData>& StartItemData = (*StartSlotData->Inventory)[StartSlotData->ItemIndex];
			
		UE_LOG(LogTemp, Warning, TEXT("thisSlotData %d ,StartSlotData %d") , thisSlotData->ItemIndex , StartSlotData->ItemIndex);


		Swap(thisItemData, StartItemData);
		//thisItemData = nullptr;
		//StartItemData = nullptr;

		//TSharedPtr<FItemData>& StartData = S

		this->SetSlot();
		StarDataData->SetSlot();

	}
}
