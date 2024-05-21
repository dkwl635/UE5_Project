// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ChaosDungeon/ChaosDungeon_MainWidget.h"
#include "Subsystem/ChaosDungeon/ChaosDungeonSubsystem.h"

void UChaosDungeon_MainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	EndMessage->SetVisibility(ESlateVisibility::Collapsed);

	if (GetWorld())
	{
		UChaosDungeonSubsystem* Subsystem = GetWorld()->GetSubsystem<UChaosDungeonSubsystem>();
		if (Subsystem)
			Subsystem->SetEndWidget(EndMessage);
	}
}

void UChaosDungeon_MainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (PurificationGage)
	{
		PurificationGage->SetProgress();
	}
}