// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class  ERPGSLOTTYPE : uint8
{
	NONE,
	INVENTORY_GEAR, //인벤토리창 슬롯
	INVENTORY_NORMARL, //인벤토리창 슬롯

	QUICK_ITEM,			//퀵아이템 슬롯

};