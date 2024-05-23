// Fill out your copyright notice in the Description page of Project Settings.
#include "DataSubsystem/DataSubsystem.h"

#include "Item/PlayerInventorySubsystem.h"
#include "Item/Item.h"

UDataSubsystem* UDataSubsystem::DataSubsystem = nullptr;
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
	{
		ConstructorHelpers::FObjectFinder<UDataTable> Asset{ TEXT("/Script/Engine.DataTable'/Game/KJW/DT_String.DT_String'") };
		DT_String = Asset.Object;
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
	//DT_Item = nullptr;
	//DT_Potion = nullptr;
	//DT_Gear = nullptr;
	//DT_Enemy = nullptr;
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
	if(!Row)
		UE_LOG(LogTemp, Warning, TEXT("No DT_Enemy"));
	
	return Row;
}

FGearData* UDataSubsystem::FindGearData(const FName& InKey)
{
	FGearData* Row = DT_Gear->FindRow<FGearData>(InKey, TEXT(""));
	ensure(Row);
	return Row;
}

FStringData* UDataSubsystem::FindStringData(const FName& InKey)
{
	FStringData* Row = DT_String->FindRow<FStringData>(InKey, TEXT(""));
	return Row;

}

