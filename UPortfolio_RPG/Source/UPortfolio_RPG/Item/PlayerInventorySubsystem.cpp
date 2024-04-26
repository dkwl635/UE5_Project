// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PlayerInventorySubsystem.h"
#include "UObject/ConstructorHelpers.h"


bool UPlayerInventorySubsystem::Init()
{	
	DataSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDataSubsystem>();
	
	if (!DataSubsystem)
	{
		return false;
	}

	
	ItemClass = UItem::StaticClass()->GetDefaultObject<UItem>();
	ItemClass->UseItem(nullptr);
	return true;

	
}
