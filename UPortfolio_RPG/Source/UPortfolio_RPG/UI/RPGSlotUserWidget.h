// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPGUserWidget.h"
#include "Interface/SlotInterface.h"
#include "RPGSlotUserWidget.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class  ERPGSLOTTYPE : uint8
{
	NONE,
	INVENTORY, //�κ��丮â ����

};

UCLASS()
class UPORTFOLIO_RPG_API URPGSlotUserWidget : public URPGUserWidget, public ISlotInterface
{
	GENERATED_BODY()
	
public :

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slot")
	ERPGSLOTTYPE SlotType;
	
	// ISlotInterface��(��) ���� ��ӵ�
	virtual	void SlotRefresh();

};
