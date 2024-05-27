// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Controller/ChaosDungeonController.h"
#include "Subsystem/ChaosDungeon/ChaosDungeonSubsystem.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Data/InputDataConfig.h"

void AChaosDungeonController::BeginPlay()
{
	Super::BeginPlay();

}

void AChaosDungeonController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		const UInputDataConfig* BasicInputDataConfig = GetDefault<UInputDataConfig>();
		EnhancedInputComponent->BindAction(BasicInputDataConfig->Move, ETriggerEvent::Started, this, &AChaosDungeonController::StartDungeon);
		EnhancedInputComponent->BindAction(BasicInputDataConfig->DefaultAttack, ETriggerEvent::Started, this, &AChaosDungeonController::StartDungeon);
		EnhancedInputComponent->BindAction(BasicInputDataConfig->Skill_Q, ETriggerEvent::Started, this, &AChaosDungeonController::StartDungeon);
		EnhancedInputComponent->BindAction(BasicInputDataConfig->Skill_W, ETriggerEvent::Started, this, &AChaosDungeonController::StartDungeon);
		EnhancedInputComponent->BindAction(BasicInputDataConfig->Skill_E, ETriggerEvent::Started, this, &AChaosDungeonController::StartDungeon);
		EnhancedInputComponent->BindAction(BasicInputDataConfig->Skill_R, ETriggerEvent::Started, this, &AChaosDungeonController::StartDungeon);
		EnhancedInputComponent->BindAction(BasicInputDataConfig->Space, ETriggerEvent::Started, this, &AChaosDungeonController::StartDungeon);
	}
}

UChaosDungeonSubsystem* AChaosDungeonController::GetDungeonSubsystem() const
{
	if (GetWorld() == nullptr)
		return nullptr;

	return GetWorld()->GetSubsystem<UChaosDungeonSubsystem>();
}

void AChaosDungeonController::StartDungeon()
{
	if (!GetDungeonSubsystem()->IsStarted())
	{
		GetDungeonSubsystem()->StartDungeon();
	}
}
