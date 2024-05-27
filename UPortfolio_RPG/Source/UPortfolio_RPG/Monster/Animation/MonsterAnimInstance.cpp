// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/Animation/MonsterAnimInstance.h"
#include "Monster/Monster.h"

UMonsterAnimInstance::UMonsterAnimInstance()
{
	IsScream = false;
}

void UMonsterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	AMonster* Pawn = Cast<AMonster>(TryGetPawnOwner());
	if (Pawn)
	{
		IsScream = Pawn->IsScream;
		IsDetach = Pawn->IsDetach;
		IsRange = Pawn->IsRange;
		IsMove = Pawn->IsMove;
		IsDead = Pawn->IsDead;

	}
}
