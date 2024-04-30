// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPGUserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Item/ItemData.h"
#include "Item/PlayerInventorySubsystem.h"
#include "RPGInvenSlotUserWidget.generated.h"

/**
 * 
 */

UCLASS()
class UPORTFOLIO_RPG_API URPGInvenSlotUserWidget : public URPGUserWidget
{
	GENERATED_BODY()

public:
	void SetSlot();
	void SetSlot(FItemData* data);
	void SlotClear();
	virtual	void RefreshUI() override;


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

	static bool bDragSlot;	
	static URPGInvenSlotUserWidget* OnDragSlot;
	static int32 DragStartIndex;
	static int32 DragEndIndex;
	UFUNCTION(BlueprintCallable)
	bool IsDrag();
	UFUNCTION(BlueprintCallable)
	void DragStart(URPGInvenSlotUserWidget* info);
	UFUNCTION(BlueprintCallable)
	void DragEnd(URPGInvenSlotUserWidget* info);
	UFUNCTION(BlueprintCallable)
	bool IsInData();
};
