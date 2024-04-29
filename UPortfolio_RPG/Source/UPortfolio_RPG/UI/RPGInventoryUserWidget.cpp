// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RPGInventoryUserWidget.h"

void URPGInventoryUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	int8 Col = 6;
	int8 Row = 42 / Col;

	for (int8 i = 0; i < Row; i++)
	{
		for (int8 k = 0; k < Col; ++k)
		{
			URPGInvenSlotUserWidget* Widget = Cast<URPGInvenSlotUserWidget>(CreateWidget(this, SlotBP));
			ensure(Widget);

			//Widget->ItemIndex = k + i * Col;
			//
			//Widget->ItemBtnHovered.BindLambda(
			//	[this](UInventoryItemUserWidget* ItemWidget)
			//	{
			//		const uint32 Index = ItemWidget->ItemIndex;
			//		LastHoveredIndex = Index;
			//		SetItemDesc(Index);
			//	}
			//);

			//Widget->ItemBtnClicked.BindUFunction(this, TEXT("OnItemBtnClicked"));

			//Items.Add(Widget);
			NormalBox->AddChildToUniformGrid(Widget, i, k);
		}
	}

}
