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
	void RefreshUI();
public:
	//Slot Data
	Inventory Inventory;
	
	UPROPERTY(EditAnywhere , BlueprintReadWrite)	
	int ItemIndex = -1;

public:
	UFUNCTION(BlueprintCallable)
	void UseItem();

	

};
