// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "SpaceCoolTimerWidget.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API USpaceCoolTimerWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable)
	void SetProgressBar();

protected:
	UPROPERTY(meta=(BindWidget))
	UProgressBar* ProgressBar;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TextBlock;
};
