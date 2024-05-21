// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/RPGUserWidget.h"
#include "Item/PlayerInventorySubsystem.h"
#include "Components/CanvasPanel.h"
#include "RPGQuickSlotsUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API URPGQuickSlotsUserWidget : public URPGUserWidget
{
	GENERATED_BODY()
	
public:
	 void Init() override;
	 void RefreshUI() override;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCanvasPanel* CanvasPanel;

	TMap<int, class URPGSlot*> QuickSlotsIndex;
public:

	void UseQuickSlot(int8 SlotIndex);


};
