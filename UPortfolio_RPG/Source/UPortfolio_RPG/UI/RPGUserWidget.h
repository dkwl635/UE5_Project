// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGUserWidget.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class UPORTFOLIO_RPG_API URPGUserWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable)
	virtual void RefreshUI();
	UFUNCTION(BlueprintCallable)
	virtual void Init();
};
