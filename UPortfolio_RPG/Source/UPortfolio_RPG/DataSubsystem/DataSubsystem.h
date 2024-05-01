// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Item/ItemData.h"
#include "DataSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API UDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UDataSubsystem();

	//나중에 게임모드쪽에 넣으면 좋을꺼 같음
	UFUNCTION(BlueprintCallable)
	void Init();
public:
	
	FItemData* FindItem(const FName& InKey);
	FPotionData* FindPotionData(const FName& InKey);
protected:

	bool bInit = false;

//ITEM
	UPROPERTY()
	UDataTable* DT_Item;

	UPROPERTY()
	UDataTable* DT_Potion;

};
