// Fill out your copyright notice in the Description page of Project Settings.
#include "Components/DropItemManager.h"
#include "DropItem.h"

TWeakObjectPtr<ADropItemManager> ADropItemManager::DropItemManager = nullptr;
// Sets default values for this component's properties
ADropItemManager::ADropItemManager()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UBlueprint> Asset{ TEXT("/Script/Engine.Blueprint'/Game/KJW/BPA_DropItem.BPA_DropItem'") };
	if (Asset.Object)
	{
		DropItemClass = (UClass*)Asset.Object->GeneratedClass;

	}
	DropItemManager = this;

	UE_LOG(LogTemp, Warning, TEXT("UDropItemManager_UDropItemManager"));
}

ADropItemManager::~ADropItemManager()
{
	Pool.Empty();
	DropItemList.Empty();
	DropItemManager = nullptr;
	UE_LOG(LogTemp, Warning, TEXT("UDropItemManager_~UDropItemManager"));
}


ADropItem* ADropItemManager::SpawnDropItem(FVector SpawnLocation)
{
	ADropItem* DropItem = nullptr;
	if (Pool.IsEmpty())
	{
		DropItem = GetWorld()->SpawnActor<ADropItem>(DropItemClass , SpawnLocation, FRotator::ZeroRotator);
		DropItemList.Add(DropItem);
		DropItem->OnRemoveItem.AddDynamic(this, &ADropItemManager::PushBackItem);
	}
	else
	{
		Pool.Dequeue( DropItem);
	}

	DropItem->SetActorHiddenInGame(false);
	DropItem->SetActorEnableCollision(true);
	DropItem->SetActorTickEnabled(true);

	return DropItem;
}

void ADropItemManager::PushBackItem(ADropItem* DropItem)
{
	UE_LOG(LogTemp, Warning, TEXT("PushBack"));
	Pool.Enqueue(DropItem);
}

