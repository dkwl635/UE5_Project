// Fill out your copyright notice in the Description page of Project Settings.


#include "DropItem.h"
#include "Item/PlayerInventorySubsystem.h"
#include "DataSubsystem/DataSubsystem.h"
#include "UI/UIManager.h"
#include "Item/ItemData.h"

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
	FItemData* data = UDataSubsystem::DataSubsystem->FindItem(ItemHande);
	FText ItemNameText = FText::FromName(data->ItemName);
	if (data == nullptr) { return FText(); }
	if (ItemCount >= 1)
	{
		FText CountText = FText::FromString(FString::FromInt(ItemCount));
		FText FormatText = FText::Format(NSLOCTEXT("YourNamespace", "YourKey", "{0} x{1}"), ItemNameText, CountText);
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

	if (UPlayerInventorySubsystem::PlayerInventorySubsystem->AddItem(ItemHande, ItemCount) == false)
	{
		return;
	}

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




