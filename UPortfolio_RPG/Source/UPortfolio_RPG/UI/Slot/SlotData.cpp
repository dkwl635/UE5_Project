// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Slot/SlotData.h"
#include "Item/PlayerInventorySubsystem.h"

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

void USlotData::SetData()
{
}

void USlotData::RefreshData()
{
}

void USlotData::ClearData()
{
}



UTexture2D* USlotData::GetSlotImg()
{
    return nullptr;
}

int32 USlotData::GetCount()
{
    return 1;
}



bool USlotData::NormalUse()
{
    return false;
}

//bool USlotData::QuickUse()
//{
//    return false;
//}
//
//bool USlotData::SpecialUse()
//{
//    return false;
//}

FItemData* USlotData::GetItemData()
{
    return nullptr;
}


