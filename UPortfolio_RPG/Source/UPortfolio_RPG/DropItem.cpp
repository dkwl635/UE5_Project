// Fill out your copyright notice in the Description page of Project Settings.


#include "DropItem.h"
#include "Item/PlayerInventorySubsystem.h"
#include "UI/UIManager.h"

// Sets default values
ADropItem::ADropItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADropItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADropItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADropItem::SetDropItem()
{
	ActionDropItem();
}

FText ADropItem::SetItemText()
{
	return FText::FromString("TestName");
}

void ADropItem::AddItem()
{
	if (ItemHande.IsNone())
	{
		RetrunItem();
		return;
	}

	UPlayerInventorySubsystem::PlayerInventorySubsystem->AddItem(ItemHande, 1);

	AUIManager::UIManager->RefreshUI(ERPG_UI::INVENTORY);
	AUIManager::UIManager->RefreshUI(ERPG_UI::QUICKSLOTS);

	RetrunItem();
}

void ADropItem::RetrunItem()
{
	this->SetActorHiddenInGame(true);
	this->SetActorEnableCollision(false);
	this->SetActorTickEnabled(false);

	if (OnRemoveItem.IsBound())
	{
		OnRemoveItem.Broadcast(this);
	}
}




