// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Skill/CoolTimerUserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "SkillSlot.generated.h"

UCLASS()
class UPORTFOLIO_RPG_API USkillSlot : public UCoolTimerUserWidget
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

	FTimerHandle CoolTimer;
};
