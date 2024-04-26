// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemData.h"
#include "Item.generated.h"


UCLASS()
class UPORTFOLIO_RPG_API UItem : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void UseItem(FItemData* ItemData)
	{
		UE_LOG(LogTemp, Warning, TEXT("TEST"));
	}

};

