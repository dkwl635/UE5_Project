// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPGSlotUserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Item/ItemData.h"
#include "Item/PlayerInventorySubsystem.h"
#include "RPGInvenSlotUserWidget.generated.h"

/**
 * 
 */

UCLASS()
class UPORTFOLIO_RPG_API URPGInvenSlotUserWidget : public URPGSlotUserWidget
{
	GENERATED_BODY()

public:
	void SetSlot();
	void SetSlot(FItemData* data);
	void SlotClear();
	virtual	void RefreshUI() override;

	// URPGSlotUserWidget을(를) 통해 상속됨
	void SlotRefresh() override;


public:
	Inventory Inventory;

	//slot btn
	UPROPERTY(meta = (BindWidget))
	UButton* SlotBtn;

	UPROPERTY(meta = (BindWidget))
	UImage* SlotImg;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)	
	int ItemIndex = -1;

public:
	UFUNCTION(BlueprintCallable)
	void UseItem();

	

};
