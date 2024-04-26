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
	uint32 CurrentBundleCount = 0;

	UPROPERTY(EditAnywhere)
	FName ItemName;
	
	UPROPERTY(EditAnywhere)
	EITEMTYPE ItemType;

	UPROPERTY(EditAnywhere)
	uint32 MaxBundleCount ;

	UPROPERTY(EditAnywhere)
	UTexture2D* ItemImage;

	UPROPERTY(EditAnywhere)
	FText ItemDesc;

	UPROPERTY(EditAnywhere)
	FDataTableRowHandle StatusData;
};


USTRUCT()
struct UPORTFOLIO_RPG_API FPotionData : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	uint32 PotionValue = 0;

	UPROPERTY(EditAnyWhere, meta = (Bitmask, BitmaskEnum = EPOTIONTYPE))
	uint8 EPotionType;
};

USTRUCT()
struct UPORTFOLIO_RPG_API FGearData : public FTableRowBase
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere)
	uint32 GearValue = 0;

	UPROPERTY(EditAnyWhere)
	EGEARTYPE EGearType;
};


USTRUCT()
struct UPORTFOLIO_RPG_API FBatlleItemData : public FTableRowBase
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere)
	uint32 FBatlleItemValue = 0;

	UPROPERTY(EditAnywhere)
	uint32 FBatlleItemType = 0;

};