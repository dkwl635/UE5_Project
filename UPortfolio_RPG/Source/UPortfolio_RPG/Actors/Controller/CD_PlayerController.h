// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Controller/BasicPlayerController.h"
#include "CD_PlayerController.generated.h"

class AChaosDungeonInfo;

UCLASS()
class UPORTFOLIO_RPG_API ACD_PlayerController : public ABasicPlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

protected:
	void InitInfo();

public:
	AChaosDungeonInfo* GetInfo() { return Info; }

protected:
	AChaosDungeonInfo* Info = nullptr;

private:
	UPROPERTY(VisibleAnywhere)
	bool IsDunGeonStarted = false;
};
