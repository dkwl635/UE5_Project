// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Animation/PlayerAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "Actors/PlayerCharacter/PlayerCharacter.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	Speed = 0.;
	bIsSpace = false;
}

void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	APawn* Pawn = TryGetPawnOwner();
	if (::IsValid(Pawn))
	{
		Character = Cast<ACharacter>(Pawn);
	}
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!Character)
		return;
	APlayerCharacter* Player = Cast<APlayerCharacter>(Character);
	Speed = Player->GetVelocity().Length();
	bIsSpace = Player->bIsSpace;
}
