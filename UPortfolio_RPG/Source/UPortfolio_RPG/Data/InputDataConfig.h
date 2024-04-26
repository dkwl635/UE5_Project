// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputDataConfig.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API UInputDataConfig : public UObject
{
	GENERATED_BODY()

public:
	UInputDataConfig();
	UInputMappingContext* InputMappingContext = nullptr;

public:
	UInputAction* Move = nullptr;
	UInputAction* DefaultAttack = nullptr;
};
