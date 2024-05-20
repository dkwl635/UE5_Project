// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "ChaosDungeonProgressUserWidget.generated.h"

UCLASS()
class UPORTFOLIO_RPG_API UChaosDungeonProgressUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	void SetProgress();
	UFUNCTION()
	void OnPressButton();

protected:
	UPROPERTY(meta=(BindWidget))
	UProgressBar* ProgressBar;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* PercentageTextBlock;
	UPROPERTY(meta=(BindWidget))
	UButton* EscapeButton;
};
