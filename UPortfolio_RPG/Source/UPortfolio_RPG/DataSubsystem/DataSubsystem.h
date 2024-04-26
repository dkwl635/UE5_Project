// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DataSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API UDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UDataSubsystem();

	UFUNCTION(BlueprintCallable)
	void Init();

protected:

	bool bInit = false;

	UPROPERTY()
	UDataTable* DataSubsystem;
	
};
