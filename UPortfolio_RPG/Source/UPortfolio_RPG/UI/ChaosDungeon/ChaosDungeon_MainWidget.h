// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Skill/Skill_MainWidget.h"
#include "UI/ChaosDungeon/ChaosDungeonProgressUserWidget.h"
#include "ChaosDungeon_MainWidget.generated.h"


UCLASS()
class UPORTFOLIO_RPG_API UChaosDungeon_MainWidget : public USkill_MainWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(meta = (BindWidget))
	UChaosDungeonProgressUserWidget* PurificationGage;
};
