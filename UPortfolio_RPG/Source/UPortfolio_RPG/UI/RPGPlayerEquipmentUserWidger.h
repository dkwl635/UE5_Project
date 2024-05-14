// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/RPGUserWidget.h"
#include "Item/ItemEnum.h"
#include "RPGPlayerEquipmentUserWidger.generated.h"

/**
 * UENUM(BlueprintType)
enum class EGEARTYPE : uint8
{
    None = 0 ,
    WEAPON = 1,
    HEAD = 2,
    ARMOR= 3,
    PANTS = 4,
    GLOVES = 5,
    SHOES = 6,

};
 */

//
UCLASS()
class UPORTFOLIO_RPG_API URPGPlayerEquipmentUserWidger : public URPGUserWidget
{
	GENERATED_BODY()

public:

	 void Init() override;
	 void RefreshUI() override;
	 void ShowInitUI() override;
	 void HideSetUI() override;

public:
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UEquipmentSlot* WeaponSlot;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UEquipmentSlot* HeadSlot;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UEquipmentSlot* ArmorSlot;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UEquipmentSlot* PantsSlot;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UEquipmentSlot* GlovesSlot;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UEquipmentSlot* ShoesSlot;

public: 
	UEquipmentSlot* GetEquipmentSlot(EGEARTYPE Type);

	
};
