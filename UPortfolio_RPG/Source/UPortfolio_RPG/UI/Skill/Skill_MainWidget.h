// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/Skill/SkillInterfaceUserWidget.h"
#include "UI/Skill/SpaceCoolTimerWidget.h"
#include "Skill_MainWidget.generated.h"


UCLASS()
class UPORTFOLIO_RPG_API USkill_MainWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

protected:
	UFUNCTION(BlueprintCallable)
	void SetUIInfo();

protected:
	UPROPERTY(meta=(BindWidget))
	USkillInterfaceUserWidget* Sk_Interface;
	UPROPERTY(meta=(BindWidget))
	USpaceCoolTimerWidget* SpaceCoolTimer;
};
