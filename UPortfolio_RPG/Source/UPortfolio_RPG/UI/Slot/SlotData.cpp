// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Slot/SlotData.h"

UWorld* FSlotData::World = nullptr;
FSlotData::FSlotData()
{
}

bool FSlotData::IsValid()
{
    return false;
}

UTexture2D* FSlotData::GetSlotImg()
{
    return nullptr;
}



bool FSlotData::NormalUse()
{
    return false;
}

bool FSlotData::QuickUse()
{
    return false;
}

bool FSlotData::SpecialUse()
{
    return false;
}
