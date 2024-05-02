// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Slot/SlotData.h"

TWeakObjectPtr<UWorld> USlotData::SlotWorld = nullptr;
TWeakObjectPtr<UPlayerInventorySubsystem> USlotData::InventorySubsystem = nullptr;
void USlotData::ClearStaticMember()
{
    SlotWorld = nullptr;
    InventorySubsystem = nullptr;
}
USlotData::USlotData()
{
}

bool USlotData::IsValid()
{
    return false;
}

UTexture2D* USlotData::GetSlotImg()
{
    return nullptr;
}



bool USlotData::NormalUse()
{
    return false;
}

bool USlotData::QuickUse()
{
    return false;
}

bool USlotData::SpecialUse()
{
    return false;
}
