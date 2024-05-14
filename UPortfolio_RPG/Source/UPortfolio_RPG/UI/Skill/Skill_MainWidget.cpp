// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Skill/Skill_MainWidget.h"
#include "Actors/PlayerCharacter/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void USkill_MainWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void USkill_MainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (SpaceCoolTimer)
	{
		SpaceCoolTimer->SetProgressBar();

		if (SpaceCoolTimer->RemainingTime >= 0.1f)
		{
			SpaceCoolTimer->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			SpaceCoolTimer->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	if (HPBar)
	{
		HPBar->SetHPBar();
	}
	if (MPBar)
	{
		MPBar->SetMPBar();
	}
}

void USkill_MainWidget::SetUIInfo()
{
	Sk_Interface->Init();
}
