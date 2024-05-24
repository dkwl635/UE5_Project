// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemData.h"
#include "DataSubsystem/DataSubsystem.h"
#include "Item.generated.h"

UCLASS()
class UPORTFOLIO_RPG_API UItem : public UObject
{
	GENERATED_BODY()
public:
	friend class UDataSubsystem;
private:
	static TMap<FName, FPotionData*> PotionDatas;
	static TWeakObjectPtr<UWorld> CurrentWorld;
private:

	FPotionData* GetPotionData(FName Name);
	
public:
	
	bool UseItem(UWorld* World ,FItemData* ItemData);

private:

	bool UsePotion(FPotionData* PotionData);

	

};

