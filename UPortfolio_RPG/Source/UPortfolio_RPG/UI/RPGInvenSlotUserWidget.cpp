// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RPGInvenSlotUserWidget.h"
#include "Item/PlayerInventorySubsystem.h"



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



void URPGInvenSlotUserWidget::UseItem()
{

	GetWorld()->GetGameInstance()->GetSubsystem<UPlayerInventorySubsystem>()->UseItem(Inventory, ItemIndex, 1);
	//SlotRefresh();

}





