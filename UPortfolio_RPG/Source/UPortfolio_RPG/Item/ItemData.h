// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemEnum.h"
#include "ItemData.generated.h"
/**
 * 
 */
class UItem;

USTRUCT()
struct UPORTFOLIO_RPG_API FItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int8 CurrentBundleCount = 0;

	UPROPERTY(EditAnywhere)
	FName ItemName = "";
	
	UPROPERTY(EditAnywhere)
	EITEMTYPE ItemType = EITEMTYPE::None;

	UPROPERTY(EditAnywhere)
	int8 MaxBundleCount  = 0;

	UPROPERTY(EditAnywhere)
	UTexture2D* ItemImage = nullptr;

	UPROPERTY(EditAnywhere)
	FText ItemDesc;

	UPROPERTY(EditAnywhere)
	FDataTableRowHandle StatusData ;
};


USTRUCT()
struct UPORTFOLIO_RPG_API FPotionData : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	int16 PotionValue = 0;

	UPROPERTY(EditAnyWhere, meta = (Bitmask, BitmaskEnum = EPOTIONTYPE))
	uint8 EPotionType = 0;
};

USTRUCT()
struct UPORTFOLIO_RPG_API FGearData : public FTableRowBase
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere)
	int16 GearValue = 0;

	UPROPERTY(EditAnyWhere)
	EGEARTYPE EGearType = EGEARTYPE::None;
};


USTRUCT()
struct UPORTFOLIO_RPG_API FBatlleItemData : public FTableRowBase
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere)
	int16 FBatlleItemValue = 0;

	UPROPERTY(EditAnywhere)
	int8 FBatlleItemType = 0;

};