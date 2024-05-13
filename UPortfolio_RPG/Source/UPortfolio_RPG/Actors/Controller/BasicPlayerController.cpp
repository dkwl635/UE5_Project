// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Controller/BasicPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "InputActionValue.h"
#include "Data/InputDataConfig.h"
#include "Actors/PlayerCharacter/PlayerCharacter.h"

ABasicPlayerController::ABasicPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
}

void ABasicPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem< UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		const UInputDataConfig* InputDataConfig = GetDefault<UInputDataConfig>();
		Subsystem->AddMappingContext(InputDataConfig->InputMappingContext, 0);
	}
	PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
}

void ABasicPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		const UInputDataConfig* BasicInputDataConfig = GetDefault<UInputDataConfig>();
		EnhancedInputComponent->BindAction(BasicInputDataConfig->Move, ETriggerEvent::Triggered, this, &ABasicPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(BasicInputDataConfig->Move, ETriggerEvent::Completed, this, &ABasicPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(BasicInputDataConfig->Move, ETriggerEvent::Canceled, this, &ABasicPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(BasicInputDataConfig->DefaultAttack, ETriggerEvent::Triggered, this, &ABasicPlayerController::OnDefaultAttack);
		EnhancedInputComponent->BindAction(BasicInputDataConfig->Skill_Q, ETriggerEvent::Started, this, &ABasicPlayerController::OnSkill_Q);
		EnhancedInputComponent->BindAction(BasicInputDataConfig->Space, ETriggerEvent::Started, this, &ABasicPlayerController::OnSpace);
		EnhancedInputComponent->BindAction(BasicInputDataConfig->OpenSkillUI, ETriggerEvent::Started, this, &ABasicPlayerController::OnOpenSkillUI);
	}

}

void ABasicPlayerController::OnSetDestinationTriggered()
{
	FHitResult Hit;
	bool bHitSuccessful = false;
	bHitSuccessful = GetHitResultUnderCursor(ECC_Visibility, false, Hit);


	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;
	}

	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
	}
}

void ABasicPlayerController::OnSetDestinationReleased()
{
	// We move there and spawn some particles
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
}

void ABasicPlayerController::OnDefaultAttack()
{
	StopMovement();
	FHitResult Hit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	PlayerCharacter->OnDefaultAttack(Hit.Location);
}

void ABasicPlayerController::OnSkill_Q(const FInputActionValue& InputActionValue)
{
	StopMovement();
	PlayerCharacter;
}

void ABasicPlayerController::OnSpace()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	PlayerCharacter->OnSpace(Hit.Location);
}

void ABasicPlayerController::OnOpenSkillUI()
{

}
