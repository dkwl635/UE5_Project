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
#include "Components/CapsuleComponent.h"
#include "Actors/Animation/PlayerAnimInstance.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	{
		SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
		CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
		StatusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("StatusComponent"));
		SkillComponent = CreateDefaultSubobject<USkillComponent>(TEXT("SkillComponent"));
		//SwordCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("SwordCollider"));
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
		SpringArmComponent->TargetArmLength = 800.f;
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
}

void APlayerCharacter::SetAnimData(const FDataTableRowHandle& InDataTableRowHandle)
{
	DataTableRowHandle = InDataTableRowHandle;
	if (DataTableRowHandle.IsNull()) { return; }
	if (DataTableRowHandle.RowName == NAME_None) { return; }
	AnimDataTableRow = DataTableRowHandle.GetRow<FCharacterAnimDataTableRow>(TEXT(""));
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
	Skill_Q_Montage = InData->Skill_Q_Montage;

	CurrentMontage = AttackMontage_A;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!DataTableRowHandle.IsNull() && DataTableRowHandle.RowName != NAME_None)
	{
		AnimDataTableRow = DataTableRowHandle.GetRow<FCharacterAnimDataTableRow>(TEXT(""));

		SetAnimData(AnimDataTableRow);
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerCharacter::OnSkill(const FVector& HitPoint)
{
	UAnimInstance* Animation = GetMesh()->GetAnimInstance();
	ensure(Animation);
	if (Animation->Montage_IsPlaying(nullptr)) { return; }

	LookAtMouseCursor(HitPoint);
	Animation->Montage_Play(Skill_Q_Montage, 1.2f);
}

void APlayerCharacter::OnSpace(const FVector& HitPoint)
{
	UAnimInstance* Animation = GetMesh()->GetAnimInstance();
	ensure(Animation);
	if (Animation->Montage_IsPlaying(nullptr)) { return; }

	// 쿨타임 타이머
	bool bIsSpaceCool = GetWorld()->GetTimerManager().IsTimerActive(SpaceCoolTimer);
	if (bIsSpaceCool) { return; }
	GetWorld()->GetTimerManager().SetTimer(SpaceCoolTimer, SpaceCoolTime, false);// 회피 5초쿨

	GetController()->StopMovement();

	if (!bIsSpace)
	{
		bIsSpace = true;
		GetController()->StopMovement();
		LookAtMouseCursor(HitPoint);
		Animation->Montage_Play(SpaceMontage, 1.2f);
	}
	auto SpaceDelegate = [this]() { bIsSpace = false; };
	GetWorld()->GetTimerManager().SetTimer(SpaceTimer, SpaceDelegate, 0.6f, false);
}

void APlayerCharacter::OnDefaultAttack(const FVector& HitPoint)
{
	if(!bOnAttack)
	{
		UAnimInstance* Animation = GetMesh()->GetAnimInstance();
		ensure(Animation);
		if (Animation->Montage_IsPlaying(nullptr)) { return; }
		
		bOnAttack = true;
		LookAtMouseCursor(HitPoint);
		Animation->Montage_Play(CurrentMontage, 1.2f);
	}
}

#include "Engine/DamageEvents.h"
void APlayerCharacter::DefaultAttackCheck()
{
	float Radius = 80.f;
	FVector Start = GetActorLocation() + GetActorForwardVector() * 120.f;
	TArray<AActor*> IgnoreActors;
	TArray<FHitResult> HitResult;

	bool bIsHit = UKismetSystemLibrary::SphereTraceMulti(this, Start, Start, Radius,
		ETraceTypeQuery::TraceTypeQuery4, false,
		IgnoreActors, EDrawDebugTrace::ForDuration, HitResult, true);
	if (bIsHit)
	{
		for(auto& It:HitResult)
		{
			if (IsValid(It.GetActor()))
			{
				AActor* DamagedActor = It.GetActor();
				FDamageEvent DamageEvent;
				DamagedActor->TakeDamage(StatusComponent->GetAttackDamage(), DamageEvent, GetController(), this);
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
