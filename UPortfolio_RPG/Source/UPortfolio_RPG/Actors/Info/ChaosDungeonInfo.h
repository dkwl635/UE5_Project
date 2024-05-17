// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "ChaosDungeonInfo.generated.h"

class ACD_PlayerController;

UCLASS()
class UPORTFOLIO_RPG_API AChaosDungeonInfo : public AInfo
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

	void InitChaosDungeon();
	void AddPurification(float InValue) { PurificationGage += InValue; }

protected:
	float PurificationGage = 0.f;
};
