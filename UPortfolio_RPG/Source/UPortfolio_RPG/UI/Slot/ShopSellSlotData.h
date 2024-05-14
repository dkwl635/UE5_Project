// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Slot/SlotData.h"
#include "ShopSellSlotData.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API UShopSellSlotData : public USlotData
{
	GENERATED_BODY()

public:
	TWeakObjectPtr<class URPGSlotUserWidget> OrginSlot;

	int32 GetCount() override;
	bool IsValid() override;
	void ClearData() override;
	UTexture2D* GetSlotImg() override;

	void RefreshData();

 bool NormalUse() override;

public:
	int8 SellCount = 0;
	
};
