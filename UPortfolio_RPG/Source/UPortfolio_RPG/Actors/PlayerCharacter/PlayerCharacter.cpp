// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PlayerCharacter/PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Components/StatusComponent.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	{
		SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
		CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
		StatusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("StatusComponent"));
	}
	{
		SpringArmComponent->SetupAttachment(GetRootComponent());
		SpringArmComponent->TargetArmLength = 1000.f;
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
		CachedWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	}
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
	bool bIsSpaceCool = GetWorld()->GetTimerManager().IsTimerActive(SpaceCoolTimer);
	if (bIsSpaceCool) { return; }
	GetWorld()->GetTimerManager().SetTimer(SpaceCoolTimer, SpaceCoolTime, false);	// 회피 5초쿨

	const FVector ActorLocation = GetActorLocation();
	const FVector Direction = (HitPoint - ActorLocation).GetSafeNormal();
	const FVector Destination = ActorLocation + Direction * SpaceDistance;
	GetController()->StopMovement();
	FRotator NewRotation = FRotationMatrix::MakeFromX(Direction).Rotator();
	SetActorRotation(NewRotation);

	LaunchCharacter(Direction * SpaceDistance, true, true);
}