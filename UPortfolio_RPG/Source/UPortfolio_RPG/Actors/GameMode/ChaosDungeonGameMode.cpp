// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/GameMode/ChaosDungeonGameMode.h"
#include "Actors/Controller/ChaosDungeonController.h"

AChaosDungeonGameMode::AChaosDungeonGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.DoNotCreateDefaultSubobject(TEXT("Sprite")))
{
	PlayerControllerClass = AChaosDungeonController::StaticClass();
}
