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
	void BuyItem(class UShopBuySlot* ShopSlot);
private:
	TWeakObjectPtr<class URPGMainUserWidget> PlayerUI;
	class URPGMainUserWidget* GetPlayerUI();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* BuyItemPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UWidgetSwitcher* ShopSwitcher;

	UPROPERTY(EditAnywhere , BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* SellPriceText;

	TArray<TWeakObjectPtr<class UShopBuySlot>> BuyShopSlotList;

public:
	int SellSlotMaxCount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* SellItemList;
	TArray<TWeakObjectPtr<class URPGSlotUserWidget>> SellShopSlotList;
	TArray<TWeakObjectPtr<class UShopSellSlotData>> SellShopSlotDataList;
;
bool CheckSellItem(class URPGSlotUserWidget* OrginSlot);

	UFUNCTION(BlueprintCallable)
	void SellItem();

	void RefreshSellPrice();

	void SetSellPrice();

};
