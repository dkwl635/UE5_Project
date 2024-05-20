// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/Monster.h"
#include "Monster/Animation/MonsterAnimInstance.h"

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
	}
}
