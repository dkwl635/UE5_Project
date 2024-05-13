// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Skill/CoolTimerUserWidget.h"
#include "SpaceCoolTimerWidget.generated.h"

UCLASS()
class UPORTFOLIO_RPG_API USpaceCoolTimerWidget : public UCoolTimerUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void SetProgressBar() override;
	
};
