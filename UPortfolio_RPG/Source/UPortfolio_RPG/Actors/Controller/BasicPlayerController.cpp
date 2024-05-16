// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Controller/BasicPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "InputActionValue.h"
#include "Data/InputDataConfig.h"
#include "Subsystem/CoolTimeSubsystem.h"
#include "GameFramework/SpringArmComponent.h"
#include "Actors/PlayerCharacter/PlayerCharacter.h"

ABasicPlayerController::ABasicPlayerController()
{
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Cursor(TEXT("/Script/Niagara.NiagaraSystem'/Game/KSH/Character/MouseCursor/FX_Cursor.FX_Cursor'"));
	ensure(Cursor.Object);
	FXCursor = Cursor.Object;
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

void ABasicPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	PawnSpringArm->TargetArmLength = FMath::Lerp(PawnSpringArm->TargetArmLength,
		TargetArmLength, DeltaSeconds * 3.f);
}

void ABasicPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	PlayerCharacter = Cast<APlayerCharacter>(aPawn);
	if (IsValid(PlayerCharacter))
	{
		/*UDataSubsystem* DataSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDataSubsystem>();
		const FCharacterDataTableRow* CharacterDataTableRow = DataSubsystem->FindChacter(TEXT("Soldier3"));

		KDT2Character->SetData(CharacterDataTableRow);*/
	}

	PawnSpringArm = aPawn->GetComponentByClass<USpringArmComponent>();
	TargetArmLength = PawnSpringArm->TargetArmLength;
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
		EnhancedInputComponent->BindAction(BasicInputDataConfig->Skill_W, ETriggerEvent::Started, this, &ABasicPlayerController::OnSkill_W);
		EnhancedInputComponent->BindAction(BasicInputDataConfig->Space, ETriggerEvent::Started, this, &ABasicPlayerController::OnSpace);
		EnhancedInputComponent->BindAction(BasicInputDataConfig->OpenSkillUI, ETriggerEvent::Started, this, &ABasicPlayerController::OnOpenSkillUI);
		EnhancedInputComponent->BindAction(BasicInputDataConfig->ZoomWheel, ETriggerEvent::Triggered, this, &ABasicPlayerController::OnZoomWheel);
	}

}

UCoolTimeSubsystem* ABasicPlayerController::GetCoolTimeManager() const
{
	if (GetLocalPlayer() == nullptr)
		return nullptr;

	return GetLocalPlayer()->GetSubsystem<UCoolTimeSubsystem>();
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
	if (ControlledPawn != nullptr && !PlayerCharacter->bIsDead)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
	}
}

void ABasicPlayerController::OnSetDestinationReleased()
{
	if(!PlayerCharacter->bIsDead)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}
}

void ABasicPlayerController::OnDefaultAttack()
{
	if (!PlayerCharacter->bIsDead)
	{
		StopMovement();
		FHitResult Hit;
		GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
		PlayerCharacter->OnDefaultAttack(Hit.Location);
	}
}

void ABasicPlayerController::OnSkill_Q()
{
	if (!PlayerCharacter->bIsDead)
	{
		FHitResult Hit;
		GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
		UCoolTimeSubsystem* CoolTimeManager = GetCoolTimeManager();
		PlayerCharacter->OnSkill_Q(Hit.Location);
	}
}

void ABasicPlayerController::OnSkill_W()
{
	if (!PlayerCharacter->bIsDead)
	{
		FHitResult Hit;
		GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
		PlayerCharacter->OnSkill_W(Hit.Location);
	}
}

void ABasicPlayerController::OnSpace()
{
	if (!PlayerCharacter->bIsDead)
	{
		FHitResult Hit;
		GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
		UCoolTimeSubsystem* CoolTimeManager = GetCoolTimeManager();
		if (!CoolTimeManager->IsSpaceCool())
		{
			CoolTimeManager->SetSpaceTimer();
			PlayerCharacter->OnSpace(Hit.Location);
		}
	}
}

void ABasicPlayerController::OnOpenSkillUI()
{

}

void ABasicPlayerController::OnZoomWheel(const FInputActionValue& InputActionValue)
{
	const float ActionValue = InputActionValue.Get<float>();

	TargetArmLength += ActionValue * -50.f;
	TargetArmLength = FMath::Clamp(TargetArmLength, 250.f, 1200.f);
}
