// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/RPGInventoryUserWidget.h"
#include "Item/PlayerInventorySubsystem.h"

void URPGInventoryUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//return;
	int32 Col = InvenSlotSizeX;
	int32 Row = InvenSlotSizeY;

	UPlayerInventorySubsystem* Inven = GetWorld()->GetGameInstance()->GetSubsystem<UPlayerInventorySubsystem>();
	if (!Inven)
	{
		return;
	}
	Inventory GearInvetory = Inven->GetInventory(EITEMTYPE::GEAR);
	Inventory NormalInvetory = Inven->GetInventory(EITEMTYPE::POTION);
	UE_LOG(LogTemp, Warning, TEXT("My Name: %d ,: %d"), Row, Col);
	
	UE_LOG(LogTemp, Warning, TEXT("My Name: %d ,: %d"), NormalSlots.Num(), GearSlots.Num());
	int32 test = 0;
	for (int32 i = 0; i < Row; i++)
	{
		for (int32 k = 0; k < Col; k++)
		{
			URPGInvenSlotUserWidget* Widget = Cast<URPGInvenSlotUserWidget>(CreateWidget(this, SlotBP));
			ensure(Widget);

		
			Widget->ItemIndex = k + i * Col;
			Widget->Inventory = GearInvetory;
			GearSlots.Add(Widget);
			GearBox->AddChildToUniformGrid(Widget, i, k);
			Widget->SlotClear();

			test++;
		}	
		
	}

	for (int32 i = 0; i < Row; i++)
	{
		for (int32 k = 0; k < Col; k++)
		{
			URPGInvenSlotUserWidget* Widget = Cast<URPGInvenSlotUserWidget>(CreateWidget(this, SlotBP));
			ensure(Widget);

		
			Widget->ItemIndex = k + i * Col;
			Widget->Inventory = NormalInvetory;
			NormalSlots.Add(Widget);
			NormalBox->AddChildToUniformGrid(Widget, i, k);
			Widget->SlotClear();
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("My Name: %d ,: %d"), NormalSlots.Num(), GearSlots.Num());
}

void URPGInventoryUserWidget::RefreshUI()
{
	int bagIndex = BagWidgetSwitcher->GetActiveWidgetIndex();
	if (bagIndex == 0)
	{
		GearInventoryRefresh();
	}
	else if (bagIndex == 1)
	{
		NormalInventoryRefresh();
	}
}

void URPGInventoryUserWidget::GearInventoryRefresh()
{
	int32 Size = GearSlots.Num();
	for (int32 i = 0; i < Size; i++)
	{
		GearSlots[i]->RefreshUI();
	}
}

void URPGInventoryUserWidget::NormalInventoryRefresh()
{
	int32 Size = NormalSlots.Num();
	for (int32 i = 0; i < Size; i++)
	{
		NormalSlots[i]->RefreshUI();
	}
}
