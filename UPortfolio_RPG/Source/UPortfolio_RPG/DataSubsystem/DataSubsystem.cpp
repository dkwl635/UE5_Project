// Fill out your copyright notice in the Description page of Project Settings.
#include "DataSubsystem/DataSubsystem.h"
#include "Item/ItemData.h"
#include "Item/PlayerInventorySubsystem.h"

UDataSubsystem::UDataSubsystem()
{
	{
		static ConstructorHelpers::FObjectFinder<UDataTable> Asset{ TEXT("/Script/Engine.DataTable'/Game/KJW/DT_ITEM.DT_ITEM'") };
		ensure(Asset.Object);
		DataSubsystem = Asset.Object;
		if (Asset.Object)
		{
			UE_LOG(LogTemp, Warning, TEXT("Succens DT_ITEM"));
		
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

	UPlayerInventorySubsystem* Inven = GetWorld()->GetGameInstance()->GetSubsystem<UPlayerInventorySubsystem>();
	if (Inven->Init())
	{
		UE_LOG(LogTemp, Warning, TEXT("Inven->Init"));
	}

		bInit = true;
}
