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
	UTexture2D* GetSlotImg() override;
	bool IsValid() override;
	bool NormalUse() override;
	void RefreshData() override;
	void ClearData() override;
	void SetData() override;
	
	//�ӽ÷� ������ �ִ� ������ ����

	TWeakPtr<struct  FItemData> ItemData;

	//���� ��ȣ�ۿ��̵Ǵ� 
	//���� ����
	EITEMTYPE ItemType = EITEMTYPE::None;
	//TWeakObjectPtr<class URPGSlotUserWidget> QuickSlot;
};