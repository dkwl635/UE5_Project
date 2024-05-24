// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Item.h"
#include "Actors/PlayerCharacter/PlayerCharacter.h"
#include "Components/StatusComponent.h"
#include "DataSubsystem/DataSubsystem.h"


TMap<FName, FPotionData*> UItem::PotionDatas;

bool UItem::UseItem(FItemData* ItemData)
{

	if (!ItemData)
	{
		return false;
	}
	UE_LOG(LogTemp, Warning, TEXT("My Item: %s"), *ItemData->ItemName.ToString());
	
	switch (ItemData->ItemType)
	{
	case EITEMTYPE::POTION:
	{
		FPotionData* PotionData = GetPotionData(ItemData->StatusData.RowName);
		bool result = UsePotion(PotionData);
		return result;
		break;
	}

	default:
		break;
	}



	
	return false;
}

FPotionData* UItem::GetPotionData(FName Name)
{

	if (!PotionDatas.Contains(Name))
	{
		FPotionData* GetData = UDataSubsystem::DataSubsystem->FindPotionData(Name);
		UE_LOG(LogTemp, Warning, TEXT("NewItemData: %s"), *Name.ToString());
		PotionDatas.Add(Name, GetData);		
	}

	return PotionDatas[Name];
	
}


bool UItem::UsePotion(FPotionData* PotionData)
{
	if (!PotionData)
	{
		return false;
	}
	//UE_LOG(LogTemp, Warning, TEXT("My Name: %d ,: %d"), PotionData->EPotionType , PotionData->PotionValue);
	
	if (PotionData->EPotionType & static_cast<uint8>(EPOTIONTYPE::HP))
	{
		UWorld* World = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport)->World();
		APlayerCharacter* Character =	Cast<APlayerCharacter>(World->GetFirstPlayerController()->GetPawn());
		UStatusComponent* Status = Character->GetStatusComponent();
		float CurrentHp = Status->GetCurrentHP();
		CurrentHp += PotionData->PotionValue;

		if (CurrentHp >= Status->GetMaxHP())
		{
			Status->SetCurrentHP(Status->GetMaxHP());
		}
		else
		{
			Status->SetCurrentHP(CurrentHp);
		}
	}

	return true;
}
