// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/RPGUserWidget.h"
#include "RPGSlotUserWidget.h"
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

	//æ∆¿Ã≈€ ΩΩ∑‘
	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	TArray<URPGSlotUserWidget*> QuickItemSlots;




};
