// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Item.h"
#include "Actors/PlayerCharacter/PlayerCharacter.h"
#include "GameInstance/RPGGameInstance.h"
#include "Components/StatusComponent.h"
#include "DataSubsystem/DataSubsystem.h"
#include "Engine/World.h"


TMap<FName, FPotionData*> UItem::PotionDatas ;
TWeakObjectPtr<UWorld> UItem::CurrentWorld = nullptr;
bool UItem::UseItem(UWorld* World ,FItemData* ItemData)
{

	if (!ItemData || !World)
	{
		return false;
	}
	
	
	CurrentWorld = World;

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
		FPotionData* GetData = RPGGameInstance->GetDataSubsyetem()->FindPotionData(Name);
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
		URPGGameInstance* GameInstance = Cast<URPGGameInstance>(CurrentWorld->GetGameInstance());
		APlayerCharacter* Character = GameInstance->GetPlayerCharacter();
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
