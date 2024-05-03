// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Animation/EnemyAnimInstance.h"
#include "Enemy/Enemy.h"

UEnemyAnimInstance::UEnemyAnimInstance()	
{
	Speed = 0.f;
}

void UEnemyAnimInstance::NativeInitializeAnimation()
{
	
}

void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	AEnemy* Pawn = Cast<AEnemy>(TryGetPawnOwner());
	if (Pawn)
	{
		FVector Velocity = Pawn->Movement->Velocity;
		Speed = FVector(Velocity.X, Velocity.Y, 0).Size();
	}

}
