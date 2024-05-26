// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/RPGUserWidget.h"
#include "RPGTextBox.generated.h"

/**
 * 
 */


UCLASS()
class UPORTFOLIO_RPG_API URPGTextBox : public URPGUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bindwidget))
	class UButton* YesButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bindwidget))
	class UButton* NoButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bindwidget))
	class UTextBlock* BoxInfo;
private:
	virtual void NativeConstruct();
public:
	
	void SetYesNoButton(FOnButtonCallBack  YesButtonFunc, FOnButtonCallBack  NoButtonFunc, FText BoxText);

private:
	FOnButtonCallBack YesButtonFunc;
	FOnButtonCallBack NoButtonFunc;
	UFUNCTION()
	void OnClickedYesButton();
	UFUNCTION()
	void OnClickedNoButton();
};
