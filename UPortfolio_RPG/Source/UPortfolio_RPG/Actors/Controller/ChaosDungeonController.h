// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Controller/BasicPlayerController.h"
#include "ChaosDungeonController.generated.h"

class UChaosDungeonSubsystem;

UCLASS()
class UPORTFOLIO_RPG_API AChaosDungeonController : public ABasicPlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UChaosDungeonSubsystem* GetDungeonSubsystem() const;

protected:
	void StartDungeon();

private:
	bool bIsStarted = false;
};
