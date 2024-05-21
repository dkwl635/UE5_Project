	// Fill out your copyright notice in the Description page of Project Settings.
#include "NPC/NPCManager.h"
#include "NPC/NPC.h"
#include "NPC/NPCTalkBoxUserwidget.h"
#include "Kismet/GameplayStatics.h"
#include "UI/RPGMainUserWidget.h"
#include "UI/UIEnum.h"
#include "UI/PlayerUIComponent.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "UI/RPGShop.h"
#include "UI/UIManager.h"
#include	"Item/ItemData.h"


ANPCManager* ANPCManager::NPCManager = nullptr;
ANPCManager::ANPCManager()
{
 	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ANPCManager::BeginPlay()
{
	Super::BeginPlay();
	NPCManager = this;
}

void ANPCManager::BeginOverlapPlayer(ANPC* Target)
{
	CurrentNPC = Target;	
}

void ANPCManager::EndOverlapPlayer(ANPC* Target)
{
	if (CurrentNPC.Get() == Target)
	{
		CurrentNPC = nullptr;
	}
}



void ANPCManager::StartInteractiorNPC()
{
	if (!CurrentNPC.IsValid())
	{
		return;
	}

	if (bInteractior == true)
	{
		return;
	}
	ReceiveStartInteractiorNPC();

}

void ANPCManager::EndInteractiorNPC()
{
	if(CurrentNPC == nullptr || !bInteractior)
	{
		return;
	}
	
	if (AUIManager::UIManager->IsShowUI(ERPG_UI::NPCTALK))
	{
		AUIManager::UIManager->HideUI(ERPG_UI::NPCTALK);
	}
	
	ReceiveEndInteractiorNPC();
}

void ANPCManager::InteractiorNPC()
{
	if (CurrentNPC != nullptr)
	{
		bInteractior = true;
		CurrentNPC->StartInteraction();

		AUIManager::UIManager->ShowUI(ERPG_UI::NPCTALK);
		return;
	}
	else
	{
		return ;
	}

}

void ANPCManager::LeaveNPC()
{
	CurrentNPC->EndInteraction();
	
	bInteractior = false;
}

void ANPCManager::OpenShopUI()
{
	if (CurrentNPC->ShopBuyData.IsEmpty())
	{
		return;
	}
	
	URPGShop* ShopUI = Cast<URPGShop>(AUIManager::UIManager->GetRPGUI(ERPG_UI::SHOP));
	ShopUI->SetShopData(CurrentNPC.Get()->ShopBuyData);

	AUIManager::UIManager->ShowUI(ERPG_UI::SHOP);
	AUIManager::UIManager->ShowUI(ERPG_UI::INVENTORY);
	

}


