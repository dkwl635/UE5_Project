// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Animation/PlayerAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "Actors/PlayerCharacter/PlayerCharacter.h"

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	Pawn = TryGetPawnOwner();
	if (IsValid(Pawn))
	{
		Speed = UKismetMathLibrary::VSize(Pawn->GetVelocity());
	}
}
