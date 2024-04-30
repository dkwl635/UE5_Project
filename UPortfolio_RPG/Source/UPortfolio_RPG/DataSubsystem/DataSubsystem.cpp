// Fill out your copyright notice in the Description page of Project Settings.
#include "DataSubsystem/DataSubsystem.h"

#include "Item/PlayerInventorySubsystem.h"

UDataSubsystem::UDataSubsystem()
{
	{
		ConstructorHelpers::FObjectFinder<UDataTable> Asset{ TEXT("/Script/Engine.DataTable'/Game/KJW/DT_ITEM.DT_ITEM'") };
		ensure(Asset.Object);
		DT_Item = Asset.Object;
		if (Asset.Object)
		{
			UE_LOG(LogTemp, Warning, TEXT("Succens DT_ITEM"));
		}
	}
	{
		ConstructorHelpers::FObjectFinder<UDataTable> Asset{ TEXT("/Script/Engine.DataTable'/Game/KJW/DT_PO.DT_PO'") };
		ensure(Asset.Object);
		DT_Potion = Asset.Object;
		if (Asset.Object)
		{
			UE_LOG(LogTemp, Warning, TEXT("Succens DT_Potion"));
		}
	}



}

void UDataSubsystem::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("UDataSubsystem->Init"));
	if (bInit)
	{
		return;
	}
	UItem::DataSubsystem = this;

	UPlayerInventorySubsystem* Inven = GetWorld()->GetGameInstance()->GetSubsystem<UPlayerInventorySubsystem>();
	if (Inven->Init())
	{
		UE_LOG(LogTemp, Warning, TEXT("Inven->Init"));
	}

		bInit = true;
}

FItemData* UDataSubsystem::FindItem(const FName& InKey)
{
	FItemData* Row = DT_Item->FindRow<FItemData>(InKey, TEXT(""));
	ensure(Row);
	return Row;

}

FPotionData* UDataSubsystem::FindPotionData(const FName& InKey)
{
	FPotionData* Row = DT_Potion->FindRow<FPotionData>(InKey, TEXT(""));
	ensure(Row);
	return Row;
}
