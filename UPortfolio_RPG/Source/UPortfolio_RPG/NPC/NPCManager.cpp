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

// Sets default values
ANPCManager::ANPCManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANPCManager::BeginPlay()
{
	Super::BeginPlay();
	
	NPCTalkBoxUserwidget = Cast<UNPCTalkBoxUserwidget>(CreateWidget<UNPCTalkBoxUserwidget>(GetWorld(), NPCUserWidget));
	NPCTalkBoxUserwidget->NPCManager = this;
	NPCTalkBoxUserwidget->SetVisibility(ESlateVisibility::Collapsed);


}

// Called every frame
void ANPCManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANPCManager::BeginOverlapPlayer(ANPC* Target)
{
	UE_LOG(LogTemp, Warning, TEXT("BeginOverlapPlayer"));
	CurrentNPC = Target;	
}

void ANPCManager::EndOverlapPlayer(ANPC* Target)
{
	if (CurrentNPC.Get() == Target)
	{
		CurrentNPC = nullptr;
	
		UE_LOG(LogTemp, Warning, TEXT("EndOverlapPlayer"));
	}
}

URPGMainUserWidget* ANPCManager::GetPlayerUI()
{
	if (!PlayerUI.IsValid())
	{
		auto PlayerControll = UGameplayStatics::GetPlayerController(GetWorld(),0);
	//	UPlayerUIComponent* Find = (UPlayerUIComponent*)(PlayerControll->GetPawn()->GetComponentByClass(UPlayerUIComponent::StaticClass()));
		UPlayerUIComponent* Find = PlayerControll->GetPawn()->FindComponentByClass<UPlayerUIComponent>();
		PlayerUI = Find->PlayerUI;
	}

	return PlayerUI.Get();
}

void ANPCManager::StartInteractiorNPC()
{
	if (bInteractior == true)
	{
		return;
	}
	//Execute_ReceiveActiveInteractiorBox();
	ReceiveStartInteractiorNPC();

}

void ANPCManager::EndInteractiorNPC()
{
	if(CurrentNPC == nullptr || !bInteractior)
	{
		return;
	}
	NPCTalkBoxUserwidget->SetVisibility(ESlateVisibility::Collapsed);
	ReceiveEndInteractiorNPC();
}

void ANPCManager::InteractiorNPC()
{
	if (CurrentNPC != nullptr)
	{
		bInteractior = true;
		CurrentNPC->StartInteraction();

		if (GetPlayerUI())
		{
			GetPlayerUI()->RPGUI->AddChildToCanvas(NPCTalkBoxUserwidget);
			UCanvasPanelSlot* Slot = Cast<UCanvasPanelSlot>(NPCTalkBoxUserwidget->Slot);
			Slot->SetZOrder(NPCZOrder);		
		}


		NPCTalkBoxUserwidget->SetVisibility(ESlateVisibility::Visible);
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

	if (GetPlayerUI())
	{
		URPGShop* ShopUI = Cast<URPGShop>( GetPlayerUI()->GetRPGUI(ERPG_UI::SHOP));
		ShopUI->SetShopData(CurrentNPC->ShopBuyData);
		GetPlayerUI()->ShowUI(ERPG_UI::SHOP);
	}

}

