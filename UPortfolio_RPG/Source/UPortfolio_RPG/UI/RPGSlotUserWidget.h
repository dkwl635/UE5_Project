// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPGUserWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Slot/SlotData.h"
#include "RPGSlotUserWidget.generated.h"



UCLASS(Blueprintable, BlueprintType)
class UPORTFOLIO_RPG_API URPGSlotUserWidget : public URPGUserWidget
{
	GENERATED_BODY()
	
public:
	//한번만 호출되는
	void Init() override;
	~URPGSlotUserWidget();
	
public:
	//UFUNCTION(BlueprintCallable)
	//void SetSlot();

	UFUNCTION(BlueprintCAllable)
	bool IsInValid();

	UFUNCTION(BlueprintCallable)
	bool UseSlot();

	//슬롯 초기화
	UFUNCTION(BlueprintCallable)
	void ClearSlot();
	//슬롯 갱신
	UFUNCTION(BlueprintCallable)
	void RefreshSlot();

	UFUNCTION(BlueprintCallable)
	FText GetCountText();


public :

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	ERPGSLOTTYPE SlotType = ERPGSLOTTYPE::NONE;

	UPROPERTY(BlueprintReadWrite , meta = (BindWidget))
	UImage* SlotImg;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* HoverImg;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CountText;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<UUserWidget> DragUserWidget;

	

public :

public:
	UPROPERTY()
	USlotData* SlotData;

	USlotData* GetSlotData();

public:
	
	UFUNCTION(BlueprintCallable)
	bool DragEnd(URPGSlotUserWidget* StarDataData);
	UFUNCTION(BlueprintCallable)
	void DragFailed(URPGSlotUserWidget* StarDataData);
	
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FDele_Dynamic_OneParam ClickSlotEvent;
};

