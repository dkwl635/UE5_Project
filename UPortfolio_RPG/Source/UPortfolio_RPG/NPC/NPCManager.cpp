// Fill out your copyright notice in the Description page of Project Settings.
#include "NPC/NPCManager.h"
#include "NPC/NPC.h"
#include "NPC/NPCTalkBoxUserwidget.h"
#include "Kismet/GameplayStatics.h"
#include "UI/RPGMainUserWidget.h"
#include "UI/UIEnum.h"

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
	
	NPCTalkBoxUserwidget =  Cast<UNPCTalkBoxUserwidget> (CreateWidget<UNPCTalkBoxUserwidget>(GetWorld(), NPCUserWidget));
	NPCTalkBoxUserwidget->NPCManager = this;
	
	UserUI = Cast<URPGMainUserWidget>(UGameplayStatics::GetActorOfClass(GetWorld(), URPGMainUserWidget::StaticClass()));

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
	NPCTalkBoxUserwidget->RemoveFromParent();
	ReceiveEndInteractiorNPC();
}

void ANPCManager::InteractiorNPC()
{
	if (CurrentNPC != nullptr)
	{
		bInteractior = true;
		CurrentNPC->StartInteraction();
		NPCTalkBoxUserwidget->AddToViewport();
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
	auto UI =	 UserUI->GetRPGUI(ERPG_UI::SHOP);
	if (UI)
	{
		UserUI->ShowUI(UI);
	}

}

