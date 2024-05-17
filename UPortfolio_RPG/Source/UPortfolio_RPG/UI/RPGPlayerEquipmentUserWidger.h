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
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta = (BindWidget))
	class URPGSlot* WeaponSlot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class URPGSlot* HeadSlot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class URPGSlot* ArmorSlot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class URPGSlot* PantsSlot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class URPGSlot* GlovesSlot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  meta = (BindWidget))
	class URPGSlot* ShoesSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* AddHpText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* AddAtkText;
public: 
	class	URPGSlot* GetEquipmentSlot(EGEARTYPE Type);

public:
	void SetAddStat();
	
};
