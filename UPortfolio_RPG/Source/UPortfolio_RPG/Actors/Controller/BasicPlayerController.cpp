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
		EnhancedInputComponent->BindAction(BasicInputDataConfig->DefaultAttack, ETriggerEvent::Started, this, &ABasicPlayerController::OnDefaultAttack);
		EnhancedInputComponent->BindAction(BasicInputDataConfig->Skill, ETriggerEvent::Started, this, &ABasicPlayerController::OnSkill);
		EnhancedInputComponent->BindAction(BasicInputDataConfig->Space, ETriggerEvent::Started, this, &ABasicPlayerController::OnSpace);
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
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}
}

void ABasicPlayerController::OnDefaultAttack()
{
	StopMovement();
}

void ABasicPlayerController::OnSkill(const FInputActionValue& InputActionValue)
{
	
}

void ABasicPlayerController::OnSpace()
{
	FHitResult Hit;
	GetHitResultUnderCursorByChannel(ETraceTypeQuery::TraceTypeQuery1, true, Hit);
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
	ensure(PlayerCharacter);
	StopMovement();
	PlayerCharacter->OnSpace(Hit.Location);
}
