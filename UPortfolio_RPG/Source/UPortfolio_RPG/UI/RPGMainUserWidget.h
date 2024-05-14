// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "RPGUserWidget.h"
#include "Components/Button.h"
#include "RPGMainUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API URPGMainUserWidget : public URPGUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY(meta = (BindWidget))
	UButton* InventoryBtn;

	TWeakObjectPtr<class UPlayerInventorySubsystem> PlayerInven;
	TWeakObjectPtr<class UPlayerInventorySubsystem> GetPlayerInven();
public	:

	virtual void Init();
	~URPGMainUserWidget();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D ViewSize;


public:
	UFUNCTION(BlueprintCallable)
	void ShowUI(ERPG_UI Type);

	void ShowUI(URPGUserWidget* UserWidget);

	UFUNCTION(BlueprintCallable)
	void HideUI(URPGUserWidget* UserWidget);
	UFUNCTION(BlueprintCallable)
	void ToggleUI(URPGUserWidget* UserWidget);
	UFUNCTION(BlueprintCallable)
	URPGUserWidget* GetRPGUI(ERPG_UI Type);
	UFUNCTION(BlueprintCallable)
	class UCanvasPanelSlot* GetCanvasPanel(ERPG_UI Type);

	UFUNCTION(BlueprintCallable)
	URPGUserWidget* RPGUIRefresh(ERPG_UI Type);


public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  meta = (BindWidget))
	class UCanvasPanel* RPGUI;

public:
	//Interaction
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bInteraction;

private:
	TMap<ERPG_UI, URPGUserWidget*> RPGUIMap;
	TMap<ERPG_UI, UCanvasPanelSlot*> RPGUICanvasMap;
	TWeakObjectPtr<UCanvasPanelSlot> TopPopupUI;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* GoldTextBlock;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CoinTextBlock;
public:
	void	PlayerGoodsRefresh();

public :
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* ItemBoxPanel;
	class UCanvasPanelSlot* ItemBoxPanelSlot;
	class UItemInfoUserWdiget* ItemBox;

	void ShowItemInfoBox(FVector2D SppawnPos, FItemData* Data);
	void HideItemInfoBox();

	FVector2D GetShowItemPos(FVector2D SppawnPos);
};
