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
#include "GameInstance/RPGGameInstance.h"
#include "Actors/PlayerCharacter/PlayerCharacter.h"
#include "Actors/Controller/BasicPlayerController.h"

ANPCManager::ANPCManager()
{
 	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ANPCManager::BeginPlay()
{
	Super::BeginPlay();
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

	RPGGameInstance->GetPlayerBasicController()->StopMovement();

	ReceiveStartInteractiorNPC();

}

void ANPCManager::EndInteractiorNPC()
{
	if(CurrentNPC == nullptr || !bInteractior)
	{
		return;
	}
	
	if (RPGGameInstance->GetUIManager()->IsShowUI(ERPG_UI::NPCTALK))
	{
		RPGGameInstance->GetUIManager()->HideUI(ERPG_UI::NPCTALK);
	}
	
	ReceiveEndInteractiorNPC();
}

void ANPCManager::InteractiorNPC()
{
	if (CurrentNPC != nullptr)
	{
		bInteractior = true;
		CurrentNPC->StartInteraction();

		RPGGameInstance->GetUIManager()->ShowUI(ERPG_UI::NPCTALK);
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
	
	URPGShop* ShopUI = Cast<URPGShop>(RPGGameInstance->GetUIManager()->GetRPGUI(ERPG_UI::SHOP));
	ShopUI->SetShopData(CurrentNPC.Get()->ShopBuyData);

	RPGGameInstance->GetUIManager()->ShowUI(ERPG_UI::SHOP);
	RPGGameInstance->GetUIManager()->ShowUI(ERPG_UI::INVENTORY);

	RPGGameInstance->GetUIManager()->GetCanvasPanel(ERPG_UI::SHOP)->SetPosition(FVector2D(311, 140));
	RPGGameInstance->GetUIManager()->GetCanvasPanel(ERPG_UI::INVENTORY)->SetPosition(FVector2D(1000, 165));
	

}


