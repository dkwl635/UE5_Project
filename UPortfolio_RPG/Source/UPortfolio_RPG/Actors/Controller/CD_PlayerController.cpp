// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Controller/CD_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Data/InputDataConfig.h"
#include "Actors/Info/ChaosDungeonInfo.h"

void ACD_PlayerController::BeginPlay()
{
	Super::BeginPlay();

}

void ACD_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		const UInputDataConfig* BasicInputDataConfig = GetDefault<UInputDataConfig>();
		EnhancedInputComponent->BindAction(BasicInputDataConfig->Move, ETriggerEvent::Started, this, &ACD_PlayerController::InitInfo);
		EnhancedInputComponent->BindAction(BasicInputDataConfig->DefaultAttack, ETriggerEvent::Started, this, &ACD_PlayerController::InitInfo);
		EnhancedInputComponent->BindAction(BasicInputDataConfig->Skill_Q, ETriggerEvent::Started, this, &ACD_PlayerController::InitInfo);
		EnhancedInputComponent->BindAction(BasicInputDataConfig->Skill_W, ETriggerEvent::Started, this, &ACD_PlayerController::InitInfo);
		EnhancedInputComponent->BindAction(BasicInputDataConfig->Space, ETriggerEvent::Started, this, &ACD_PlayerController::InitInfo);
	}
}

void ACD_PlayerController::InitInfo()
{
	if (!IsDunGeonStarted)
	{
		IsDunGeonStarted = true;
		Info = GetWorld()->SpawnActor<AChaosDungeonInfo>();

		Info->InitChaosDungeon();
	}

	
}
