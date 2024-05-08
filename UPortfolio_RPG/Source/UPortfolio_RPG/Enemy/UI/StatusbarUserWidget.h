// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "StatusbarUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API UStatusbarUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetHP(const float CurrentHP, const float MaxHP);

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* HPBar = nullptr;
};
