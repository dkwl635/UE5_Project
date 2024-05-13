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
		static ConstructorHelpers::FObjectFinder<UAnimMontage> Anim(TEXT("/Script/Engine.AnimMontage'/Game/KSH/Character/Animation/Attack_PrimaryA_Montage.Attack_PrimaryA_Montage'"));
		ensure(Anim.Object);
		AttackMontage_A = Anim.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UAnimMontage> Anim(TEXT("/Script/Engine.AnimMontage'/Game/KSH/Character/Animation/Attack_PrimaryB_Montage.Attack_PrimaryB_Montage'"));
		ensure(Anim.Object);
		AttackMontage_B = Anim.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UAnimMontage> Anim(TEXT("/Script/Engine.AnimMontage'/Game/KSH/Character/Animation/Attack_PrimaryC_Montage.Attack_PrimaryC_Montage'"));
		ensure(Anim.Object);
		AttackMontage_C = Anim.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UAnimMontage> Anim(TEXT("/Script/Engine.AnimMontage'/Game/KSH/Character/Animation/AnimMontage_Evade.AnimMontage_Evade'"));
		ensure(Anim.Object);
		SpaceMontage = Anim.Object;
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
	CurrentMontage = AttackMontage_A;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
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

void APlayerCharacter::OnSkill(const FInputActionValue& InputActionValue)
{

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
	FHitResult HitResult;

	bool bIsHit = UKismetSystemLibrary::SphereTraceSingle(this, Start, Start, Radius,
		ETraceTypeQuery::TraceTypeQuery4, false,
		IgnoreActors, EDrawDebugTrace::None, HitResult, true);
	if (bIsHit)
	{
		if(IsValid(HitResult.GetActor()))
		{
			AActor* DamagedActor = HitResult.GetActor();
			FDamageEvent DamageEvent;
			DamagedActor->TakeDamage(StatusComponent->GetAttackDamage(), DamageEvent, GetController(), this);
		}
	}
}

void APlayerCharacter::LookAtMouseCursor(const FVector& HitPoint)
{
	const FVector ActorLocation = GetActorLocation();
	const FVector Direction = (HitPoint - ActorLocation).GetSafeNormal();
	const FVector Destination = ActorLocation + Direction * SpaceDistance;
	FRotator CurrentRotation = GetActorRotation();
	FRotator NewRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	NewRotation.Pitch = CurrentRotation.Pitch;
	NewRotation.Roll = CurrentRotation.Roll;
	SetActorRotation(NewRotation);
}


// add LJY
float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	float CurrentHP = StatusComponent->GetHP();
	float NewHP = CurrentHP - StatusComponent->GetAttackDamage();
	StatusComponent->SetHP(NewHP);
	UE_LOG(LogTemp, Warning, TEXT("Character_HP : %f"), StatusComponent->GetHP());

	return Damage;
}