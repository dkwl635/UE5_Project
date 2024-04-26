// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UPortfolio_RPG/DataSubsystem/DataSubsystem.h"
#include "Item.h"
#include "PlayerInventorySubsystem.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API UPlayerInventorySubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()


public : 
	UFUNCTION()
	bool Init();
	

	
public:

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	int32 PlayerCoin = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 PlayerGold = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EnchantStone = 0;

	
public:

	const UDataSubsystem* DataSubsystem;
	UItem* ItemClass;
};
