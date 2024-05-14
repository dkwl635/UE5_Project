// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/RPGSlotUserWidget.h"
#include "EquipmentSlot.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API UEquipmentSlot : public URPGSlotUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GEAR")
	EGEARTYPE EGearType = EGEARTYPE::None;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GEAR")
	class UImage* GearTypeBG;

	struct FGearData* GetGearData();

};
