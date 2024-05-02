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
	INVENTORY_GEAR, //�κ��丮â ����
	INVENTORY_NORMARL, //�κ��丮â ����

	QUICK_ITEM,			//�������� ����

};

UCLASS()
class UPORTFOLIO_RPG_API URPGSlotUserWidget : public URPGUserWidget
{
	GENERATED_BODY()
	
public:
	void InitSlot();
	~URPGSlotUserWidget();


	int32 TestInt = 0;
public:
	UFUNCTION(BlueprintCallable)
	void SetSlot();

	UFUNCTION(BlueprintCAllable)
	bool IsInValid();

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
	UPROPERTY()
	USlotData* SlotData;

	USlotData* GetSlotData();

public:
	
	UFUNCTION(BlueprintCallable)
	void DragEnd(URPGSlotUserWidget* StarDataData);
};

