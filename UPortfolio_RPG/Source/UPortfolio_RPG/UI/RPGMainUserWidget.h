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

	
private:

	virtual void Init();
	~URPGMainUserWidget();

public:
	UFUNCTION(BlueprintCallable)
	void ShowUI(UUserWidget* UserWidget);
	UFUNCTION(BlueprintCallable)
	void HideUI(UUserWidget* UserWidget);
	UFUNCTION(BlueprintCallable)
	void ToggleUI(UUserWidget* UserWidget);
	UFUNCTION(BlueprintCallable)
	URPGUserWidget* GetRPGUI(ERPG_UI Type);
	UFUNCTION(BlueprintCallable)
	class UCanvasPanel* GetCanvasPanel(ERPG_UI Type);

public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  meta = (BindWidget))
	class UCanvasPanel* RPGUI;

public:
	//Interaction
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bInteraction;

	
private:

	TMap<ERPG_UI, URPGUserWidget*> RPGUIMap;
	TMap<ERPG_UI, UCanvasPanel*> RPGUICanvasMap;

};
