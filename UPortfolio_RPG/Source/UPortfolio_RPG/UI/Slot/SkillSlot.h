// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "SkillSlot.generated.h"

UCLASS()
class UPORTFOLIO_RPG_API USkillSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetImage(UTexture2D* InTexture);

protected:
	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* Canvas;
	UPROPERTY(meta = (BindWidget))
	UImage* Sk_Icon;
};
