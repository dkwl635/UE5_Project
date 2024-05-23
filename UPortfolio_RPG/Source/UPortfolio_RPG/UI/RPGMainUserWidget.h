// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "RPGUserWidget.h"
#include "Components/Button.h"
#include "RPGMainUserWidget.generated.h"

/**
 * 
 */
struct FItemData;

UCLASS()
class UPORTFOLIO_RPG_API URPGMainUserWidget : public URPGUserWidget
{
	GENERATED_BODY()


public	:

	virtual void Init();
	~URPGMainUserWidget();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D ViewSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D MousePotion;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsPush;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* RPGUI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class USkill_MainWidget* SkillWidget;

	//TextBox
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UCanvasPanel* TextBoxCanvas;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class URPGTextBox* TextBox;

public:

	UFUNCTION(BlueprintCallable)
	void UIMoveStart(ERPG_UI Type);
	UFUNCTION(BlueprintCallable)
	void UIMoveTick();
	UFUNCTION(BlueprintCallable)
	void UIMoveEnd(ERPG_UI Type);

public:
	UFUNCTION(BlueprintCallable)
	void SetViewSize(FVector2D Size);

public:
	UFUNCTION(BlueprintCallable)
	URPGUserWidget* GetRPGUI(ERPG_UI Type);
	
	UFUNCTION(BlueprintCallable)
	class UCanvasPanelSlot* GetCanvasPanel(ERPG_UI Type);
	
	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	class UCanvasPanelSlot* MoveTargetCanvasSlot;
	
	URPGUserWidget* RPGUIRefresh(ERPG_UI Type);

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
	void PlayerGoodsRefresh();

public :
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* ItemBoxPanel;
	class UCanvasPanelSlot* ItemBoxPanelSlot;
	class UItemInfoUserWdiget* ItemBox;

	void ShowItemInfoBox(FVector2D SppawnPos,struct ShowBoxData Data);
	void HideItemInfoBox();

	FVector2D GetShowItemPos(FVector2D SppawnPos);
	
	FVector2D GetViewSize();

public:
	UFUNCTION(BlueprintCallable)
	void UIButtonFunc(ERPG_UI Type);



};
