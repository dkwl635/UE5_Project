// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/UIEnum.h"
#include "UI/Slot/SlotEnum.h"
#include "RPGSlot.generated.h"


UCLASS()
class UPORTFOLIO_RPG_API URPGSlot : public UUserWidget
{
	GENERATED_BODY()
private:
	const FName ItemRemoveCheckString = "ItemRemoveCheckString";

public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* SlotImg;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* HoverImg;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CountText;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	ERPGSLOTTYPE RPGSlotType = ERPGSLOTTYPE::NONE;
	int SlotIndex = -1;

	int Option1 = -1;
	int Option2 = -1;
	int Option3 = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> DragUserWidget;
private:
	class UPlayerInventorySubsystem* GetInven();
	class UDataSubsystem* GetData();
public:
	

	void RefreshSlotUI();

	UFUNCTION(BlueprintCallable)
	bool UseSlot();
	UFUNCTION(BlueprintCallable)
	bool IsInValue();

	void ClearSlot();
	
	class UTexture2D* GetSlotImg();
	FName GetFName();
	FText GetDescFText();

public:

	UFUNCTION(BlueprintCallable)
	bool DragEnd(URPGSlot* StartSlot);
	UFUNCTION(BlueprintCallable)
	void DragFailed(URPGSlot* ThisSlot);

	UFUNCTION(BlueprintCallable)
	void ShowItemInfo();
	UFUNCTION(BlueprintCallable)
	void HideItemInfo();

public:
	UFUNCTION()
	void RemoveOrginSlotData();


};
