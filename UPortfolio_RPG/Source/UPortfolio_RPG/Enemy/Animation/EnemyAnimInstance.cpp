// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Animation/EnemyAnimInstance.h"
#include "Enemy/Enemy.h"

UEnemyAnimInstance::UEnemyAnimInstance()	
{
	Speed = 0.f;
	static ConstructorHelpers::FObjectFinder<UAnimMontage> Attack_Montage(TEXT("/Script/Engine.AnimMontage'/Game/LJY/Animation/PrimeAnimMontage.PrimeAnimMontage'"));
	if (Attack_Montage.Succeeded())
	{
		AttackMontage = Attack_Montage.Object;
	}

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

void UEnemyAnimInstance::PlayAttackMontage()
{
	//if (!Montage_IsPlaying(AttackMontage))
	{
		Montage_Play(AttackMontage, 1.0f);
	}
}
