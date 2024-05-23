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
	EQUIPMENT,
	NPCTALK,

	TEXTBOX,
};

static int TextZOrder = 6;
static int  TopZOrder = 5;
static int  PopupZOrder = 4;
static int  NPCZOrder = 2;
static int  HUDZOrder = 1;

//typedef void(*ButtonCallBack)();
DECLARE_DELEGATE(FOnButtonCallBack);