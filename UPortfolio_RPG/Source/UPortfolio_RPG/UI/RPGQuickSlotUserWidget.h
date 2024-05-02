// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/RPGUserWidget.h"
#include "RPGSlotUserWidget.h"
#include "Item/PlayerInventorySubsystem.h"
#include "Components/CanvasPanel.h"
#include "RPGQuickSlotUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API URPGQuickSlotUserWidget : public URPGUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void Init();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCanvasPanel* CanvasPanel;


	//ex) 1번 퀵슬롯의 슬로UI연결
	TMap<int8, URPGSlotUserWidget*> QuickSlotsIndex;
	//ex)1번 퀵슬롯 인벤토리 넘버와 연결
	TMap<int8, int8 > QuickIndexInvenIndex;



public:
	void SetSlot(URPGSlotUserWidget* InvetorySlotInfo);

	void UseQuickSlot(int8 SlotIndex);


};
