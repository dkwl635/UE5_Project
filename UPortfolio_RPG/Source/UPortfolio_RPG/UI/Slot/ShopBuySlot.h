// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/RPGUserWidget.h"
#include "ShopBuySlot.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API UShopBuySlot : public URPGUserWidget
{
	GENERATED_BODY()

public:
	virtual void RefreshUI();

	virtual void Init();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class URPGSlotUserWidget* ItemSlot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ItemNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PriceText;

private:
	TWeakObjectPtr<class UShopSlotData> BuySlotData;
	FItemData* BuyItemInfo;
	
	int32 BuyPrice;
	int32 BuyCount;

public :
	void SetShopBuySlot( struct FItemData* BuyItem, int32 Price, int32 Count);






};
