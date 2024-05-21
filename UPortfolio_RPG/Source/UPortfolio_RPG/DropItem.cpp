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

void ADropItem::SetDropItem(FName ItemRowName, int Count)
{
	ItemHande = ItemRowName;
	ItemCount = Count;

	ActionDropItem();
}

FText ADropItem::SetItemText()
{
	if (ItemCount > 1)
	{		
		FText CountText = FText::FromString(FString::FromInt(ItemCount));
		FText ItemNameText = FText::FromName(ItemHande);
		
		FText FormatText = FText::Format(NSLOCTEXT("YourNamespace", "YourKey", "{0} x{1}"), ItemNameText, CountText );
		return FormatText;
	}

	return FText::FromName(ItemHande);
}

void ADropItem::AddItem()
{
	if (ItemHande.IsNone())
	{
		RetrunItem();
		return;
	}

	UPlayerInventorySubsystem::PlayerInventorySubsystem->AddItem(ItemHande, ItemCount);

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




