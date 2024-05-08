// Fill out your copyright notice in the Description page of Project Settings.
#include "NPC/NPCTalkBoxUserwidget.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UNPCTalkBoxUserwidget::OpenUI()
{
	TextBoxSwitcher->SetActiveWidgetIndex(0);
}
