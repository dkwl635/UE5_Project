// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "SlotData.h"
#include "InventorySlotData.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API UInventorySlotData : public USlotData
{
	GENERATED_BODY()

public:
	UInventorySlotData();

	// USlotData을(를) 통해 상속됨
	void SetData() override;
	int32 GetCount() override;
	bool IsValid() override;
	bool NormalUse() override;
	void RefreshData() override;
	void ClearData() override;
	UTexture2D* GetSlotImg() override;
	//임시로 가지고 있는 아이템 정보

	TWeakPtr<struct  FItemData> ItemData;

	//서로 상호작용이되는 
	//원본 슬롯
	EITEMTYPE ItemType = EITEMTYPE::None;
	//TWeakObjectPtr<class URPGSlotUserWidget> QuickSlot;
};