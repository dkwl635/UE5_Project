// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/RPGUserWidget.h"
#include "Components/UniformGridPanel.h"
#include "RPGInvenSlotUserWidget.h"
#include "RPGInventoryUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API URPGInventoryUserWidget : public URPGUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* NormalBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<URPGInvenSlotUserWidget> SlotBP;

};
