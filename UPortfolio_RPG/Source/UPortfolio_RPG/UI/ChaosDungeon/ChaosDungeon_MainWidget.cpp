// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ChaosDungeon/ChaosDungeon_MainWidget.h"

void UChaosDungeon_MainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (PurificationGage)
	{
		PurificationGage->SetProgress();
	}
}