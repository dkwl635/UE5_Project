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
#include "Components/PostProcessComponent.h"
#include "UI/Skill/CoolTimerUserWidget.h"
#include "Actors/Skill/CastingSkill.h"
#include "Item/PlayerInventorySubsystem.h"
#include "Actors/Damage/PrintDamageTextActor.h"
#include "Engine/DamageEvents.h"

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
		PostProcessComponent = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcess"));
		PostProcessComponent->SetupAttachment(GetRootComponent());
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
		static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("/Script/Engine.Material'/Game/KSH/Character/Skill/Material/MT_PostProcess_SkillRange.MT_PostProcess_SkillRange'"));
		ensure(Material.Object);
		PostProcessSkill = Material.Object;
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

	if (PostProcessSkill)
	{
		UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(PostProcessSkill, this);
		PostProcessComponent->AddOrUpdateBlendable(DynamicMaterial);
		PostProcessComponent->bEnabled = false;
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GetCharacterMovement()->MaxWalkSpeed = StatusComponent->GetSpeed();

	ShowSkillDistance();
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

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
		if (!Manager->IsSkillCool(Skill) && StatusComponent->GetCurrentMP() >= Skill->Sk_ManaUsage)
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
		if (!Manager->IsSkillCool(Skill) && StatusComponent->GetCurrentMP() >= Skill->Sk_ManaUsage)
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
		if (!Manager->IsSkillCool(Skill) && StatusComponent->GetCurrentMP() >= Skill->Sk_ManaUsage)
		{
			if (Skill->CurrentSkillState == ESkillState::Idle)
			{
				Skill->ActiveSkill(Animation);
				TargetingCircleInstance->SetActorHiddenInGame(false);
			}
			else
			{
				LookAtMouseCursor(HitPoint);
				PlayerController->StopMovement();
				TargetingCircleInstance->SetActorHiddenInGame(true);
				Skill->ActiveSkill(Animation);
				Manager->SetSkillTimer(Skill);
			}
		}
	}
}

void APlayerCharacter::OnSkill_R(const FVector& HitPoint)
{
	UAnimInstance* Animation = GetMesh()->GetAnimInstance();
	ensure(Animation);
	if (Animation->Montage_IsPlaying(nullptr)) { return; }
	if (ACastingSkill* Skill = Cast<ACastingSkill>(GetSkillComponent()->Skills[2]))
	{
		TargetingCircleInstance->SetActorHiddenInGame(true);
		Skill->CurrentSkillState = ESkillState::Idle;
	}
	ASkillBase* Skill = GetSkillComponent()->Skills[3];
	ABasicPlayerController* PlayerController = Cast<ABasicPlayerController>(GetController());
	if (PlayerController)
	{
		UCoolTimeSubsystem* Manager = PlayerController->GetCoolTimeManager();
		if (!Manager->IsSkillCool(Skill) && StatusComponent->GetCurrentMP() >= Skill->Sk_ManaUsage)
		{
			PlayerController->StopMovement();
			LookAtMouseCursor(HitPoint);
			Manager->SetSkillTimer(Skill);
			if (Skill)
			{
				Skill->ActiveSkill(Animation);
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
				float Damage = StatusComponent->GetRandDamage();
				
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

void APlayerCharacter::DisplayDamage(float InDamage)
{
	const float RandX = FMath::RandRange(0, 100);
	const float RandY = FMath::RandRange(0, 100);
	const float RandZ = FMath::RandRange(0, 100);
	const FVector RandVector = FVector(RandX, RandY, RandZ);
	APrintDamageTextActor* Actor = GetWorld()->SpawnActor<APrintDamageTextActor>
		(APrintDamageTextActor::StaticClass());
	Actor->SetWidgetText(this, InDamage, GetActorLocation() + RandVector);
}

void APlayerCharacter::ShowSkillDistance()
{
	ACastingSkill* Skill = Cast<ACastingSkill>(GetSkillComponent()->Skills[2]);
	if (Skill->CurrentSkillState == ESkillState::Targeting)
	{
		PostProcessComponent->bEnabled = true;
		FVector MouseWorldPosition = GetMouseWorldPosition();
		FVector CenterLocation = GetActorLocation();
		float Distance = FVector::Dist(CenterLocation, MouseWorldPosition);
		UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>(PostProcessComponent->Settings.WeightedBlendables.Array[0].Object);
		if (DynamicMaterial)
		{
			DynamicMaterial->SetVectorParameterValue("CharacterPosition", FLinearColor(CenterLocation.X, CenterLocation.Y, CenterLocation.Z));
			DynamicMaterial->SetScalarParameterValue("SkillRange", Skill->Sk_MaxDistance);
			if (Skill->Sk_MaxDistance >= Distance)
			{
				TargetingCircleInstance->SetActorLocation(MouseWorldPosition);
			}
		}
	}
	else
	{
		PostProcessComponent->bEnabled = false;
	}
}

// When Gear Changed
void APlayerCharacter::SetGearData()
{
	Inventory = GetGameInstance()->GetSubsystem<UPlayerInventorySubsystem>();

	const int32 AddHP = Inventory->GetPlayerAddMaxHp();
	const float CurrentMaxHP = StatusComponent->GetMaxHP();
	StatusComponent->SetMaxHP(CurrentMaxHP + AddHP);
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float InDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	float Damage = FMath::RandRange(InDamage * 0.9f, InDamage * 1.1f);
	DisplayDamage(Damage);
	StatusComponent->DamageToCurrentHP(Damage);
	if (StatusComponent->GetCurrentHP() <= 0.f)
	{
		bIsDead = true;
	}

	return Damage;
}
