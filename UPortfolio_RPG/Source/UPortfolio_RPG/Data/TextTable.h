// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "CoreMinimal.h"
#include "TextTable.generated.h"

USTRUCT()
struct UPORTFOLIO_RPG_API FStringData : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	int32 TextIndex = 0;

	UPROPERTY(EditAnywhere)
	FText ItemDesc;
};