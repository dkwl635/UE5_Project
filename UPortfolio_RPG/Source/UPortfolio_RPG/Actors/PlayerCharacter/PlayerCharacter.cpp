// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PlayerCharacter/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/StatusComponent.h"
#include "Components/SkillComponent.h"
#include "Actors/Skill/SkillBase.h"
#include "UI/Skill/Skill_MainWidget.h"
#include "Actors/Animation/PlayerAnimInstance.h"
#include "Actors/Controller/BasicPlayerController.h"
#include "Subsystem/CoolTimeSubsystem.h"
#include "UI/UIManager.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	{
		SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
		CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
		StatusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("StatusComponent"));
		SkillComponent = CreateDefaultSubobject<USkillComponent>(TEXT("SkillComponent"));
	}
	{
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> Asset(TEXT("/Script/Engine.SkeletalMesh'/Game/AddContent/ParagonGreystone/Characters/Heroes/Greystone/Meshes/Greystone.Greystone'"));
		ensure(Asset.Object);
		GetMesh()->SetSkeletalMesh(Asset.Object);
		GetMesh()->SetRelativeLocation(FVector(0., 0., -88.));
		GetMesh()->SetRelativeRotation(FRotator(0., -90., 0.));
		GetMesh()->SetupAttachment(GetRootComponent());
	}
	{
		static ConstructorHelpers::FClassFinder<UAnimInstance> Anim(TEXT("/Script/Engine.AnimBlueprint'/Game/KSH/Character/Animation/BPA_Player.BPA_Player_C'"));
		ensure(Anim.Class);
		GetMesh()->SetAnimInstanceClass(Anim.Class);
	}
	{
		SpringArmComponent->SetupAttachment(GetRootComponent());
		SpringArmComponent->TargetArmLength = 1200.f;
		SpringArmComponent->bInheritPitch = false;
		SpringArmComponent->bInheritRoll = false;
		SpringArmComponent->bInheritYaw = false;
		SpringArmComponent->SetRelativeRotation(FRotator(-45., -45., 0.));
		SpringArmComponent->bUsePawnControlRotation = true;
		SpringArmComponent->bDoCollisionTest = false;
	}
	CameraComponent->SetupAttachment(SpringArmComponent);
	bUseControllerRotationYaw = false;

	{
		GetCharacterMovement()->RotationRate = FRotator(0., 1440., 0.);
		GetCharacterMovement()->bOrientRotationToMovement = true;
		GetCharacterMovement()->MaxAcceleration = 10000.f;
	}
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void APlayerCharacter::SetAnimData(const FDataTableRowHandle& InDataTableRowHandle)
{
	AnimDataTableRowHandle = InDataTableRowHandle;
	if (AnimDataTableRowHandle.IsNull()) { return; }
	if (AnimDataTableRowHandle.RowName == NAME_None) { return; }
	AnimDataTableRow = AnimDataTableRowHandle.GetRow<FCharacterAnimDataTableRow>(TEXT(""));
	SetAnimData(AnimDataTableRow);
}

void APlayerCharacter::SetAnimData(const FCharacterAnimDataTableRow* InData)
{
	ensure(InData);
	if (!InData) { return; }

	AnimDataTableRow = InData;
	AttackMontage_A = InData->AttackMontage_A;
	AttackMontage_B = InData->AttackMontage_B;
	AttackMontage_C = InData->AttackMontage_C;
	SpaceMontage = InData->SpaceMontage;

	CurrentMontage = AttackMontage_A;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!StatusDataTableRowHandle.IsNull() && StatusDataTableRowHandle.RowName != NAME_None)
	{
		StatusDataTableRow = StatusDataTableRowHandle.GetRow<FStatusDataTableRow>(TEXT(""));

		StatusComponent->SetStatusData(StatusDataTableRow);
	}
	if (!SkillDataTableRowHandle.IsNull() && SkillDataTableRowHandle.RowName != NAME_None)
	{
		SkillDataTableRow = SkillDataTableRowHandle.GetRow<FSkillDataTableRow>(TEXT(""));

		SkillComponent->SetSkillData(SkillDataTableRow);

		if (AUIManager::UIManager != nullptr) { AUIManager::UIManager->SetSkillUI(); }

	}
	if (!AnimDataTableRowHandle.IsNull() && AnimDataTableRowHandle.RowName != NAME_None)
	{
		AnimDataTableRow = AnimDataTableRowHandle.GetRow<FCharacterAnimDataTableRow>(TEXT(""));

		SetAnimData(AnimDataTableRow);
	}

	TargetingCircleInstance = GetWorld()->SpawnActor<AActor>(TargetingCircleActor);
	if (TargetingCircleInstance)
	{
		TargetingCircleInstance->SetActorHiddenInGame(true);
	}
}

#include "Actors/Skill/CastingSkill.h"
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (StatusComponent->GetCurrentHP() <= 0.f)
		bIsDead = true;
	else
		bIsDead = false;
	GetCharacterMovement()->MaxWalkSpeed = StatusComponent->GetSpeed();

	ACastingSkill* Skill = Cast<ACastingSkill>(GetSkillComponent()->Skills[2]);
	if (Skill->CurrentSkillState == ESkillState::Targeting)
	{
		FVector MouseWorldPosition = GetMouseWorldPosition();
		TargetingCircleInstance->SetActorLocation(MouseWorldPosition);
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
#include "UI/Skill/CoolTimerUserWidget.h"
void APlayerCharacter::OnSkill_Q(const FVector& HitPoint)
{
	UAnimInstance* Animation = GetMesh()->GetAnimInstance();
	ensure(Animation);
	if (Animation->Montage_IsPlaying(nullptr)) { return; }
	if (ACastingSkill* Skill = Cast<ACastingSkill>(GetSkillComponent()->Skills[2]))
	{
		TargetingCircleInstance->SetActorHiddenInGame(true);
		Skill->CurrentSkillState = ESkillState::Idle;
	}
	ASkillBase* Skill = GetSkillComponent()->Skills[0];
	ABasicPlayerController* PlayerController = Cast<ABasicPlayerController>(GetController());
	if (PlayerController)
	{
		UCoolTimeSubsystem* Manager = PlayerController->GetCoolTimeManager();
		if (Manager->IsSkillCool(Skill))
		{
			return;
		}
		else
		{
			PlayerController->StopMovement();
			Manager->SetSkillTimer(Skill);
			LookAtMouseCursor(HitPoint);
			if (Skill)
				Skill->ActiveSkill(Animation);
		}
	}
}

void APlayerCharacter::OnSkill_W(const FVector& HitPoint)
{
	UAnimInstance* Animation = GetMesh()->GetAnimInstance();
	ensure(Animation);
	if (Animation->Montage_IsPlaying(nullptr)) { return; }
	if (ACastingSkill* Skill = Cast<ACastingSkill>(GetSkillComponent()->Skills[2]))
	{
		TargetingCircleInstance->SetActorHiddenInGame(true);
		Skill->CurrentSkillState = ESkillState::Idle;
	}
	ASkillBase* Skill = GetSkillComponent()->Skills[1];
	ABasicPlayerController* PlayerController = Cast<ABasicPlayerController>(GetController());
	if (PlayerController)
	{
		UCoolTimeSubsystem* Manager = PlayerController->GetCoolTimeManager();
		if (Manager->IsSkillCool(Skill))
		{
			return;
		}
		else
		{
			PlayerController->StopMovement();
			Manager->SetSkillTimer(Skill);
			LookAtMouseCursor(HitPoint);
			if (Skill)
				Skill->ActiveSkill(Animation);
		}
	}
}

void APlayerCharacter::OnSkill_E(const FVector& HitPoint)
{
	UAnimInstance* Animation = GetMesh()->GetAnimInstance();
	ensure(Animation);
	if (Animation->Montage_IsPlaying(nullptr)) { return; }
	ASkillBase* Skill = GetSkillComponent()->Skills[2];
	ABasicPlayerController* PlayerController = Cast<ABasicPlayerController>(GetController());
	if (PlayerController)
	{
		UCoolTimeSubsystem* Manager = PlayerController->GetCoolTimeManager();
		if (Manager->IsSkillCool(Skill))
		{
			return;
		}
		else
		{
			PlayerController->StopMovement();
			LookAtMouseCursor(HitPoint);
			
			if (Skill->CurrentSkillState == ESkillState::Idle)
			{
				Skill->ActiveSkill(Animation);
				TargetingCircleInstance->SetActorHiddenInGame(false);
			}
			else
			{
				TargetingCircleInstance->SetActorHiddenInGame(true);
				Skill->ActiveSkill(Animation);
				Manager->SetSkillTimer(Skill);
			}
		}
	}
}

void APlayerCharacter::OnSpace(const FVector& HitPoint)
{
	if (!bIsSpace)
	{
		UAnimInstance* Animation = GetMesh()->GetAnimInstance();
		UPlayerAnimInstance* Anim = Cast<UPlayerAnimInstance>(Animation);
		ensure(Anim);
		if (Anim->Montage_IsPlaying(nullptr)) { Anim->Montage_Stop(0.2f); }

		if (ACastingSkill* Skill = Cast<ACastingSkill>(GetSkillComponent()->Skills[2]))
		{
			TargetingCircleInstance->SetActorHiddenInGame(true);
			Skill->CurrentSkillState = ESkillState::Idle;
		}

		FOnMontageEnded SpaceMontageDelegate;
		SpaceMontageDelegate.Unbind();
		SpaceMontageDelegate.BindUObject(this, &APlayerCharacter::OnSpaceMontageEnded);

		bIsSpace = true;
		GetController()->StopMovement();
		LookAtMouseCursor(HitPoint);
		Anim->Montage_Play(SpaceMontage, 1.2f);
		Anim->Montage_SetEndDelegate(SpaceMontageDelegate, SpaceMontage);
	}
}

void APlayerCharacter::OnSpaceMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	bIsSpace = false;
}

void APlayerCharacter::OnDefaultAttack(const FVector& HitPoint)
{
	if(!bOnAttack)
	{
		UAnimInstance* Animation = GetMesh()->GetAnimInstance();
		ensure(Animation);
		if (Animation->Montage_IsPlaying(nullptr)) { return; }
		
		if (ACastingSkill* Skill = Cast<ACastingSkill>(GetSkillComponent()->Skills[2]))
		{
			TargetingCircleInstance->SetActorHiddenInGame(true);
			Skill->CurrentSkillState = ESkillState::Idle;
		}

		bOnAttack = true;
		LookAtMouseCursor(HitPoint);
		Animation->Montage_Play(CurrentMontage, 1.2f);
	}
}

#include "Engine/DamageEvents.h"
void APlayerCharacter::DefaultAttackCheck()
{
	float Radius = 150.f;
	FVector Start = GetActorLocation() + GetActorForwardVector() * 150.f;
	TArray<AActor*> IgnoreActors;
	TArray<FHitResult> HitResult;
	TSet<AActor*> AlreadyDamagedActors;

	bool bIsHit = UKismetSystemLibrary::SphereTraceMulti(this, Start, Start, Radius,
		ETraceTypeQuery::TraceTypeQuery3, false,
		IgnoreActors, EDrawDebugTrace::None, HitResult, true);
	if (bIsHit)
	{
		for (auto& Hit : HitResult)
		{
			AActor* DamagedActor = Hit.GetActor();
			if (IsValid(DamagedActor) && !AlreadyDamagedActors.Contains(DamagedActor))
			{
				float Damage = FMath::RandRange(StatusComponent->GetMinAttackDamage(), StatusComponent->GetMaxAttackDamage());
				FDamageEvent DamageEvent;
				DamagedActor->TakeDamage(Damage, DamageEvent, GetController(), this);
				AlreadyDamagedActors.Add(DamagedActor); // 공격한 대상을 세트에 추가
			}
		}
	}
}

void APlayerCharacter::LookAtMouseCursor(const FVector& HitPoint)
{
	const FVector ActorLocation = GetActorLocation();
	const FVector Direction = (HitPoint - ActorLocation).GetSafeNormal();
	FRotator CurrentRotation = GetActorRotation();
	FRotator NewRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewRotation.Pitch = CurrentRotation.Pitch;
	NewRotation.Roll = CurrentRotation.Roll;
	SetActorRotation(NewRotation);
}

FVector APlayerCharacter::GetMouseWorldPosition()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		float MouseX, MouseY;
		PlayerController->GetMousePosition(MouseX, MouseY);

		FVector WorldLocation, WorldDirection;
		PlayerController->DeprojectScreenPositionToWorld(MouseX, MouseY, WorldLocation, WorldDirection);

		FHitResult HitResult;
		FVector Start = WorldLocation;
		FVector End = Start + (WorldDirection * 10000.0f);

		if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility))
		{
			return HitResult.Location;
		}
	}

	return FVector::ZeroVector;
}

#include "Actors/Damage/PrintDamageTextActor.h"
void APlayerCharacter::DisplayDamage(float InDamage)
{
	const float RandX = FMath::RandRange(0, 50);
	const float RandY = FMath::RandRange(0, 50);
	const float RandZ = FMath::RandRange(0, 50);
	const FVector RandVector = FVector(RandX, RandY, RandZ);
	APrintDamageTextActor* Actor = GetWorld()->SpawnActor<APrintDamageTextActor>
		(APrintDamageTextActor::StaticClass());
	Actor->SetWidgetText(this, InDamage, GetActorLocation() + RandVector);
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float InDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	float Damage = FMath::RandRange(InDamage * 0.9f, InDamage * 1.1f);
	float CurrentHP = StatusComponent->GetCurrentHP();
	float NewHP = CurrentHP - Damage;
	DisplayDamage(Damage);
	StatusComponent->SetCurrentHP(NewHP);

	return Damage;
}
