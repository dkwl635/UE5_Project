// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "CoolTimeSubsystem.generated.h"

UCLASS()
class UPORTFOLIO_RPG_API UCoolTimeSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
	
public:
	bool IsSpaceCool();
	float GetSpaceCool() { return SpaceCoolTime; }
	void SetSpaceTimer();
	float GetSpaceRemainingTime();


private:
	FTimerHandle SpaceTimer;

private:
	float SpaceCoolTime = 5.f;

	float RemainingTime;
};