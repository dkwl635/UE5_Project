// Fill out your copyright notice in the Description page of Project Settings.
#include "DataSubsystem/DataSubsystem.h"
#include "UI/Slot/SlotData.h"
#include "Item/PlayerInventorySubsystem.h"
#include "Item/Item.h"

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
	{
		ConstructorHelpers::FObjectFinder<UDataTable> Asset{ TEXT("/Script/Engine.DataTable'/Game/KJW/DT_GEARDATA.DT_GEARDATA'") };
		ensure(Asset.Object);
		DT_Gear = Asset.Object;
		if (Asset.Object)
		{
			UE_LOG(LogTemp, Warning, TEXT("Succens DT_GEARITEM"));
		}
	}


	//Enemy
	{
		ConstructorHelpers::FObjectFinder<UDataTable> Asset{ TEXT("/Script/Engine.DataTable'/Game/LJY/DT_Enemy2.DT_Enemy2'") };
		ensure(Asset.Object);
		DT_Enemy = Asset.Object;
		if (Asset.Object)
		{
			UE_LOG(LogTemp, Warning, TEXT("Succens DT_Enemy"));
		}
	}


}

UDataSubsystem::~UDataSubsystem()
{
	UItem::DataSubsystem = nullptr;
	
	DataSubsystem = nullptr;
}

void UDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	DataSubsystem = this;
}

void UDataSubsystem::Init()
{
	


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

FEnemyData* UDataSubsystem::FindEnemyData(const FName& InKey)
{
		FEnemyData* Row = DT_Enemy->FindRow<FEnemyData>(InKey, TEXT(""));
		ensure(Row);
	
		UE_LOG(LogTemp, Warning, TEXT("No DT_Enemy"));
	
	return Row;
}

FGearData* UDataSubsystem::FindGearData(const FName& InKey)
{
	FGearData* Row = DT_Gear->FindRow<FGearData>(InKey, TEXT(""));
	ensure(Row);
	return Row;
}

