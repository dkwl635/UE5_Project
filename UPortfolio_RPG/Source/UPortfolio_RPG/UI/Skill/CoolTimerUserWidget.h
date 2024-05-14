// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "CoolTimerUserWidget.generated.h"

UCLASS()
class UPORTFOLIO_RPG_API UCoolTimerUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void SetProgressBar();
	void SetSkillCoolTime(float InCoolTime);

	float MaxTime;
	float RemainingTime;

protected:
	UPROPERTY(meta=(BindWidget))
	UProgressBar* ProgressBar;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* TextBlock;
};
