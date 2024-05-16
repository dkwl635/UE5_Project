// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/RPGUserWidget.h"
#include "Components/UniformGridPanel.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "RPGInventoryUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API URPGInventoryUserWidget : public URPGUserWidget
{
	GENERATED_BODY()

protected:
	virtual void Init() override;
	
public:
	virtual void RefreshUI() override;
	void GearInventoryRefresh();
	void NormalInventoryRefresh();

	

public:
	UPROPERTY(meta = (BindWidget))
	UButton* GearButton;

	UPROPERTY(meta = (BindWidget))
	UButton* NormalButton;

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* GearBox;

	UPROPERTY(meta = (BindWidget))
	UUniformGridPanel* NormalBox;
	UPROPERTY(EditAnywhere , BlueprintReadWrite, meta = (BindWidget))
	UWidgetSwitcher* BagWidgetSwitcher;


	

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	int32 InvenSlotSizeX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 InvenSlotSizeY;

	TArray<class URPGSlot*> NormalSlots;
	TArray<class URPGSlot*> GearSlots;
		

};
