// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "PlayerStatusBarUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API UPlayerStatusBarUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetHPBar();
	void SetMPBar();

protected:
	UPROPERTY(meta=(BindWidget))
	UProgressBar* ProgressBar;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* MaxStatusTextBlock;
	UPROPERTY(meta=(BindWidget))
	UTextBlock* CurrentStatusTextBlock;

};
