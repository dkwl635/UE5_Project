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
	class UImage* ItemImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ItemCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ItemNameText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* PriceText;

public:
	struct FItemData* BuyItemInfo;
	FName ItemRowName;
	int32 BuyPrice;
	int32 BuyCount;
public :
	void SetShopBuySlot( struct FItemData* BuyItem, FName RowName, int32 Price, int32 Count);
	UFUNCTION(BlueprintCallable)
	void BuyItem();
public:
	TWeakObjectPtr<class URPGShop> ShopHelper;





};
