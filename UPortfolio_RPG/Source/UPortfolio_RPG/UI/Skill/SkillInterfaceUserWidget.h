// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "UI/Slot/SkillSlot.h"
#include "SkillInterfaceUserWidget.generated.h"

UCLASS()
class UPORTFOLIO_RPG_API USkillInterfaceUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	USkillInterfaceUserWidget(const FObjectInitializer& ObjectInitializer);
	void Init();

protected:
	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* OuterCanvasPanel;
	UPROPERTY(meta=(BindWidget))
	UImage* BackGround;
	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* InnerCanvasPanel;
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	USkillSlot* UI_SkillSlot_0;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	USkillSlot* UI_SkillSlot_1;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	USkillSlot* UI_SkillSlot_2;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	USkillSlot* UI_SkillSlot_3;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	USkillSlot* UI_SkillSlot_4;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	USkillSlot* UI_SkillSlot_5;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	USkillSlot* UI_SkillSlot_6;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	USkillSlot* UI_SkillSlot_7;
};