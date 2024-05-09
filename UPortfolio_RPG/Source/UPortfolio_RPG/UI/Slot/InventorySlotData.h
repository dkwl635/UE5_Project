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

	// USlotData��(��) ���� ��ӵ�
	void SetData() override;
	int32 GetCount() override;
	bool IsValid() override;
	bool NormalUse() override;
	void RefreshData() override;
	void ClearData() override;
	UTexture2D* GetSlotImg() override;
	//�ӽ÷� ������ �ִ� ������ ����

	TWeakPtr<struct  FItemData> ItemData;

	//���� ��ȣ�ۿ��̵Ǵ� 
	//���� ����
	EITEMTYPE ItemType = EITEMTYPE::None;
	//TWeakObjectPtr<class URPGSlotUserWidget> QuickSlot;
};