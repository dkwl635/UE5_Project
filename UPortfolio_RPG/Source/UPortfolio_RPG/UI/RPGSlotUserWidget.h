// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPGUserWidget.h"
#include "Components/Image.h"
#include "Slot/SlotData.h"
#include "RPGSlotUserWidget.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class  ERPGSLOTTYPE : uint8
{
	NONE,
	INVENTORY_GEAR, //인벤토리창 슬롯
	INVENTORY_NORMARL, //인벤토리창 슬롯

};

UCLASS()
class UPORTFOLIO_RPG_API URPGSlotUserWidget : public URPGUserWidget
{
	GENERATED_BODY()
	
public:
	void InitSlot();
	~URPGSlotUserWidget();

public:
	UFUNCTION(BlueprintCallable)
	void SetSlot();

	UFUNCTION(BlueprintCallable)
	bool UseSlot();

public :

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	ERPGSLOTTYPE SlotType;

	UPROPERTY(BlueprintReadWrite , meta = (BindWidget))
	UImage* SlotImg;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* HoverImg;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UUserWidget> DragUserWidget;

public :
	static UUserWidget* DragUserWidgetPonter;
	UFUNCTION(BlueprintCallable)
	UUserWidget* GetDragUserWidget();

public:
	TSharedPtr<FSlotData> SlotData;
	FSlotData* GetSlotData();

public:
	
	UFUNCTION(BlueprintCallable)
	void DragEnd(URPGSlotUserWidget* StarDataData);
};

