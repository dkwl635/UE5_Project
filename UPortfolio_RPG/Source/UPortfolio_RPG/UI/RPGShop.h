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
	virtual void SetShopData(TArray<struct FShopBuyItemData> ShopList);
	void BuyItem(class UShopBuySlot* ShopSlot);
private:
	TWeakObjectPtr<class URPGMainUserWidget> PlayerUI;
	class URPGMainUserWidget* GetPlayerUI();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UUniformGridPanel* BuyItemPanel;
	TArray<TWeakObjectPtr<class UShopBuySlot>> BuyShopSlotList;
};
