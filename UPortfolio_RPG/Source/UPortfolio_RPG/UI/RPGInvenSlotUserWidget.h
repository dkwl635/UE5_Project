// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "RPGInvenSlotUserWidget.generated.h"

/**
 * 
 */

UCLASS()
class UPORTFOLIO_RPG_API URPGInvenSlotUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:



	//slot btn
	UPROPERTY(meta = (BindWidget))
	UButton* SlotBtn;

	UPROPERTY(meta = (BindWidget))
	UImage* SlotImg;

	
};
