// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPGUserWidget.h"
#include "Components/Image.h"
#include "Slot/SlotData.h"
#include "RPGSlotUserWidget.generated.h"



UCLASS(Blueprintable, BlueprintType)
class UPORTFOLIO_RPG_API URPGSlotUserWidget : public URPGUserWidget
{
	GENERATED_BODY()
	
public:
	void Init() override;
	~URPGSlotUserWidget();


	
public:
	UFUNCTION(BlueprintCallable)
	void SetSlot();

	UFUNCTION(BlueprintCAllable)
	bool IsInValid();

	UFUNCTION(BlueprintCallable)
	bool UseSlot();

public :

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	ERPGSLOTTYPE SlotType = ERPGSLOTTYPE::NONE;

	UPROPERTY(BlueprintReadWrite , meta = (BindWidget))
	UImage* SlotImg;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* HoverImg;

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
};

