// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ChaosDungeon/ChaosDungeonEndUserWidget.h"

void UChaosDungeonEndUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Button->OnPressed.AddDynamic(this, &UChaosDungeonEndUserWidget::OnPressed);
}

void UChaosDungeonEndUserWidget::OnPressed()
{
	this->RemoveFromParent();
}
