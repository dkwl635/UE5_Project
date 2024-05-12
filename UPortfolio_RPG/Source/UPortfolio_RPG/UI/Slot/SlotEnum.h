// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class  ERPGSLOTTYPE : uint8
{
	NONE,
	INVENTORY_GEAR, //
	INVENTORY_NORMARL, //

	QUICK_ITEM,			//

	SHOP_ITEM, //
	SHOP_SELLITEM,

};