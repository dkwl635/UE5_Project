// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/RPGUserWidget.h"
#include "RPGShop.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API URPGShop : public URPGUserWidget
{
	GENERATED_BODY()

protected:
	virtual void Init() override;

public:
	virtual void RefreshUI() override;
	virtual void ShowInitUI() override;
	virtual void HideSetUI() override;
	virtual void SetShopData(TArray<struct FShopBuyItemData> ShopList);
public:
	void BuyItem(class UShopBuySlot* ShopSlot);
private:
	TWeakObjectPtr<class URPGMainUserWidget> PlayerUI;
	class URPGMainUserWidget* GetPlayerUI();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* BuyItemPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UWidgetSwitcher* ShopSwitcher;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* SellPriceText;

	TArray<TWeakObjectPtr<class UShopBuySlot>> BuyShopSlotList;

public:
	int SellSlotMaxCount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* SellItemList;
	TArray<TWeakObjectPtr<class URPGSlot>> SellShopSlotList;

private:
	int32 SellItemPrice;
public:
	bool CheckSellItem(class URPGSlot* OrginSlot);
	class URPGSlot* GetEmptySellSlot();
	UFUNCTION(BlueprintCallable)
	void SellItem();

	void ClearSellPrice();

	void SetSellPrice();

	void RefreshSellSlot();
	void RefreshBuySlot();

};
