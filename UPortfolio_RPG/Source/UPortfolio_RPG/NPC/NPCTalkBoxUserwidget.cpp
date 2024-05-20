// Fill out your copyright notice in the Description page of Project Settings.
#include "NPC/NPCTalkBoxUserwidget.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Button.h"
#include "UI/UIEnum.h"
#include "NPC/NPCManager.h"

void UNPCTalkBoxUserwidget::OpenUI()
{

}

void UNPCTalkBoxUserwidget::HideSetUI()
{
	ANPCManager::NPCManager->EndInteractiorNPC();
}

void UNPCTalkBoxUserwidget::OpenShop()
{
	ANPCManager::NPCManager->EndInteractiorNPC();
	ANPCManager::NPCManager->OpenShopUI();
}
