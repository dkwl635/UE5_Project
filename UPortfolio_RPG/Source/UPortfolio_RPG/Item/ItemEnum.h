// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EITEMTYPE : uint8
{
    None = 0,
    COIN = 1,
    GOLD = 2,
    ENCHANT = 3,
    QUEST = 4,
    POTION = 5,
    GEAR = 6,
    BATTLEITEM = 7,
    OTHER ,
};

UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class EPOTIONTYPE : uint8
{
    None = 0,
    HP = 1 << 1,
    MP = 1 << 2,

    ALL = HP + MP,
};

UENUM(BlueprintType)
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

UENUM(BlueprintType)
enum class ESTAT : uint8
{
   None = 0,
   HP = 1,
   ATK = 2,


};



