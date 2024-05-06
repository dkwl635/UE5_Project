// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPGUserWidget.h"
#include "Components/Button.h"
#include "RPGMainUserWidget.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ERPG_UI : uint8
{
	NONE,
	INVENTORY,
	QUICKSLOTS,
};


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
	UUserWidget* GetRPGUI(ERPG_UI UI_Type);
public :
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	URPGUserWidget* InventoryUI;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	URPGUserWidget* QuickSlotsUI;
	


	
private:

	TMap<ERPG_UI, UUserWidget*> RPGUIMap;

};
