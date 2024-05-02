// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PlayerCharacter/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
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
		SwordCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("SwordCollider"));
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
		ConstructorHelpers::FClassFinder<UAnimInstance> Anim(TEXT("/Script/Engine.AnimBlueprint'/Game/KSH/Character/Animation/BPA_Player.BPA_Player_C'"));
		ensure(Anim.Class);
		GetMesh()->SetAnimInstanceClass(Anim.Class);
	}
	{
		ConstructorHelpers::FObjectFinder<UAnimMontage> Anim(TEXT("/Script/Engine.AnimMontage'/Game/AddContent/ParagonGreystone/Characters/Heroes/Greystone/Animations/Attack_PrimaryA_Montage.Attack_PrimaryA_Montage'"));
		ensure(Anim.Object);
		AttackMontage = Anim.Object;
	}
	{
		ConstructorHelpers::FObjectFinder<UAnimMontage> Anim(TEXT("/Script/Engine.AnimMontage'/Game/AddContent/Frank_Slash_Pack/Frank_RPG_Warrior/Animations/Frank_Warrior_IP/Warrior_Evade_F_IP_Montage.Warrior_Evade_F_IP_Montage'"));
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
	SwordCollider->SetupAttachment(GetMesh(), TEXT("sword_bottom"));
	SwordCollider->SetRelativeLocation(FVector(0., 0., 60.));
	SwordCollider->SetRelativeScale3D(FVector(0.37, 0.37, 1.662500));
	SwordCollider->bHiddenInGame = false;
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
	// 쿨타임 타이머
	UAnimInstance* Animation = GetMesh()->GetAnimInstance();
	ensure(Animation);
	if (Animation->Montage_IsPlaying(nullptr)) { return; }

	bool bIsSpaceCool = GetWorld()->GetTimerManager().IsTimerActive(SpaceCoolTimer);
	if (bIsSpaceCool) { return; }
	GetWorld()->GetTimerManager().SetTimer(SpaceCoolTimer, SpaceCoolTime, false);// 회피 5초쿨

	GetController()->StopMovement();

	if (!bIsSpace)
	{
		bIsSpace = true;
		const FVector ActorLocation = GetActorLocation();
		const FVector Direction = (HitPoint - ActorLocation).GetSafeNormal();
		const FVector Destination = ActorLocation + Direction * SpaceDistance;
		GetController()->StopMovement();
		FRotator NewRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
		SetActorRotation(NewRotation);
		Animation->Montage_Play(SpaceMontage, 1.2f);
		LaunchCharacter(Direction * SpaceDistance, true, true);
	}
	auto SpaceDelegate = [this]() { bIsSpace = false; };
	GetWorld()->GetTimerManager().SetTimer(SpaceTimer, SpaceDelegate, 0.6f, false);
}

void APlayerCharacter::OnDefaultAttack(const FVector& HitPoint)
{
	UAnimInstance* Animation = GetMesh()->GetAnimInstance();
	ensure(Animation);
	if(AttackMontage)
	{
		if (Animation->Montage_IsPlaying(nullptr)) { return; }
		const FVector ActorLocation = GetActorLocation();
		const FVector Direction = (HitPoint - ActorLocation).GetSafeNormal();
		const FVector Destination = ActorLocation + Direction * SpaceDistance;
		FRotator CurrentRotation = GetActorRotation();
		FRotator NewRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
		NewRotation.Pitch = CurrentRotation.Pitch;
		NewRotation.Roll = CurrentRotation.Roll;
		SetActorRotation(NewRotation);
		Animation->Montage_Play(AttackMontage, 1.2f);
	}
}