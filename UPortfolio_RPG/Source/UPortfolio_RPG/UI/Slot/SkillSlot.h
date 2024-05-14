// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Skill/CoolTimerUserWidget.h"
#include "Components/CanvasPanel.h"
#include "Components/Image.h"
#include "SkillSlot.generated.h"

class ASkillBase;

UCLASS()
class UPORTFOLIO_RPG_API USkillSlot : public UCoolTimerUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	virtual void SetProgressBar() override;
	void SetCachedSkill(int32 Index);

	UTextBlock* GetKeyPadTextBlock() { return ShowKeyPadTextBlock; }

protected:
	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* Canvas;
	UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
	UTextBlock* ShowKeyPadTextBlock;
	
	ASkillBase* CachedSkill;
};
