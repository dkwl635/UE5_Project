// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Slot/SlotData.h"
#include "EquipmentSlotData.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API UEquipmentSlotData : public USlotData
{
	GENERATED_BODY()

public:
	UEquipmentSlotData();
	bool IsValid() override;

	void SetData()override;

	void RefreshData() override;

	void ClearData() override;

	UTexture2D* GetSlotImg() override;

	int32 GetCount() override;

	bool NormalUse() override;


	TSharedPtr<FItemData>* PlayerInventory;
	//TWeakObjectPtr<class URPGSlotUserWidget> OrginSlot;

	//ShowItem
	struct FItemData* GetItemData();

	TWeakPtr<struct FGearData> GearData;
	struct FGearData* GetGearData();
};
