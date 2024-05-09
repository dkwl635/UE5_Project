// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Slot/SlotData.h"
#include "ShopSlotData.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API UShopSlotData : public USlotData
{
	GENERATED_BODY()

public:
	void SetShopData(struct FItemData* NewData , int32 Count);

	int32 GetCount() override;
	bool IsValid() override;

	void ClearData() override;
	UTexture2D* GetSlotImg() override;

private:

	//Buy Item Info
	struct  FItemData* ItemData;
	int32 BuyCount;
	
};
