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
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	StatusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("StatusComponent"));
	
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->TargetArmLength = 1000.f;
	SpringArmComponent->bInheritPitch = false;
	SpringArmComponent->bInheritRoll = false;
	SpringArmComponent->bInheritYaw = false;
	SpringArmComponent->SetRelativeRotation(FRotator(-45., -45., 0.));
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bDoCollisionTest = false;
	CameraComponent->SetupAttachment(SpringArmComponent);

	bUseControllerRotationYaw = false;

	GetCharacterMovement()->RotationRate = FRotator(0., 1440., 0.);
	GetCharacterMovement()->bOrientRotationToMovement = true;

	CachedWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bSpace)
	{
		GetCharacterMovement()->MaxWalkSpeed = 6200.f;
		if (!(GetWorld()->GetTimerManager().IsTimerActive(SpaceDelayTimer)))
			bSpace = false;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = CachedWalkSpeed;
	}
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
	bool bIsSpaceCool = GetWorld()->GetTimerManager().IsTimerActive(SpaceCoolTimer);
	if (bIsSpaceCool) { return; }
	GetWorld()->GetTimerManager().SetTimer(SpaceCoolTimer, 5.f, false);	// 회피 5초쿨
	
	CachedWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	bSpace = true;

	FVector ActorLocation = GetActorLocation();
	FVector Direction;

	Direction = UKismetMathLibrary::GetDirectionUnitVector(ActorLocation, HitPoint);
	
	FVector Destination = ActorLocation + (Direction * SpaceDistance);

	GetWorld()->GetTimerManager().SetTimer(SpaceDelayTimer, 1.f, false);
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), Destination);
}