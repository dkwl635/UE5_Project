// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "ChaosDungeonEndUserWidget.generated.h"

UCLASS()
class UPORTFOLIO_RPG_API UChaosDungeonEndUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

protected:
	UFUNCTION()
	void OnPressed();

protected:
	UPROPERTY(meta=(BindWidget))
	UButton* Button;
};
