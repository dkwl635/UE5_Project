// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Animation/EnemyAnimInstance.h"
#include "Enemy/Enemy.h"

UEnemyAnimInstance::UEnemyAnimInstance()	
{
	IsSpawn = false;
	IsDead = false;
	Speed = 0.f;
}


void UEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	AEnemy* Pawn = Cast<AEnemy>(TryGetPawnOwner());
	if (Pawn)
	{
		FVector Velocity = Pawn->Movement->Velocity;
		Speed = FVector(Velocity.X, Velocity.Y, 0).Size();
		IsDead = Pawn->IsDead;
		IsSpawn = Pawn->IsSpawn;
		IsAttacking = Pawn->IsAttacking;
	}
}

void UEnemyAnimInstance::PlayAttackMontage()
{
	if (AttackMontage)
	{
		FOnMontageEnded AttackMontageDelegate;
		AttackMontageDelegate.Unbind();
		AttackMontageDelegate.BindUObject(this, &UEnemyAnimInstance::OnAttackMontageEnded);
		Montage_Play(AttackMontage, 1.0f);
		Montage_SetEndDelegate(AttackMontageDelegate, AttackMontage);
	}
}

void UEnemyAnimInstance::PlaySpawnMontage()
{
	if (SpawnMontage)
	{
		FOnMontageEnded SpawnMontageDelegate;
		SpawnMontageDelegate.Unbind();
		SpawnMontageDelegate.BindUObject(this, &UEnemyAnimInstance::OnSpawnMontageEnded);
		Montage_Play(SpawnMontage, 1.0f);
		Montage_SetEndDelegate(SpawnMontageDelegate, SpawnMontage);
	}
}

void UEnemyAnimInstance::OnSpawnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsSpawn = true;
	UE_LOG(LogTemp, Warning, TEXT("Spawn Success!"));
}

void UEnemyAnimInstance::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	IsAttacking = false;
	UE_LOG(LogTemp, Warning, TEXT("Attack Ended"));
}
