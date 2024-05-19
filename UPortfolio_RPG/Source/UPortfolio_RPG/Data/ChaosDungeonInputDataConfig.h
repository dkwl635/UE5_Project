// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "ChaosDungeonInputDataConfig.generated.h"

UCLASS()
class UPORTFOLIO_RPG_API UChaosDungeonInputDataConfig : public UObject
{
	GENERATED_BODY()

public:
	UChaosDungeonInputDataConfig();
	UInputMappingContext* InputMappingContext = nullptr;

public:
	UInputAction* StartMove = nullptr;
};
