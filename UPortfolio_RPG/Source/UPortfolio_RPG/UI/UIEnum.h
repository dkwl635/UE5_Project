// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ERPG_UI : uint8
{
	NONE,
	INVENTORY,
	QUICKSLOTS,
	SHOP,
};

int TopZOrder = 5;
int PopupZOrder = 4;
int NPCZOrder = 2;
int HUDZOrder = 1;