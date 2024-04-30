// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RPGInvenSlotUserWidget.h"

bool URPGInvenSlotUserWidget::bDragSlot = false;
URPGInvenSlotUserWidget* URPGInvenSlotUserWidget::OnDragSlot = nullptr;
int32 URPGInvenSlotUserWidget::DragStartIndex = -1;
int32 URPGInvenSlotUserWidget::DragEndIndex = -1;

void URPGInvenSlotUserWidget::SetSlot()
{
	if (!Inventory)
		return;
	
	FItemData* data = (*Inventory)[ItemIndex].Get();
	SetSlot(data);
}

void URPGInvenSlotUserWidget::SetSlot(FItemData* data)
{
	if (!data)
		return;

	SlotImg->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	SlotImg->SetBrushFromTexture(data->ItemImage);

}

void URPGInvenSlotUserWidget::SlotClear()
{
	SlotImg->SetVisibility(ESlateVisibility::Hidden);
}

void URPGInvenSlotUserWidget::RefreshUI()
{
	if (!Inventory)
		return;


	FItemData* data = (*Inventory)[ItemIndex].Get();

	if (data == nullptr)
	{
		SlotClear();
	}
	else
	{
		SetSlot();
	}

}

void URPGInvenSlotUserWidget::DragStart(URPGInvenSlotUserWidget* info)
{
	OnDragSlot = info;
	bDragSlot = true;
}

bool URPGInvenSlotUserWidget::IsDrag()
{
	return bDragSlot;
}

void URPGInvenSlotUserWidget::DragEnd(URPGInvenSlotUserWidget* info)
{

	bDragSlot = false;
	OnDragSlot = nullptr;
}

bool URPGInvenSlotUserWidget::IsInData()
{
	if(!Inventory || ItemIndex < 0)
	{
		return false;
	}

	FItemData* data = (*Inventory)[ItemIndex].Get();
	if (data)
	{
		return true;
	}
	
	return false;
}

