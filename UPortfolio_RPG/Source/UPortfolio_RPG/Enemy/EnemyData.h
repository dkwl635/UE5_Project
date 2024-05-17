// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyData.generated.h"

class Enemy;

USTRUCT()
struct UPORTFOLIO_RPG_API FEnemyData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Mesh")
	float CapsuleRadius;              //캡슐 컴포넌트 반지름

	UPROPERTY(EditAnywhere, Category = "Mesh")
	float CapsuleHalfHeight;          //캡슐 컴포넌트 반높이

	UPROPERTY(EditAnywhere, Category = "Mesh")
	USkeletalMesh* SkeletalMesh;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	FTransform SkeletalMeshTransform;   //enemy 상대적 위치

	UPROPERTY(EditAnywhere, Category = "Status")
	float EnemyHP;

	UPROPERTY(EditAnywhere, Category = "Status")
	float EnemyAttackDamage;

	UPROPERTY(EditAnywhere, Category = "Anim")
	TSubclassOf<UAnimInstance> AnimClass;   //애니메이션

	UPROPERTY(EditAnywhere, Category = "Particle")
	UParticleSystem* ParticleAttackSystem;

	UPROPERTY(EditAnywhere, Category = "Particle")
	UParticleSystemComponent* ParticleAttackSystemComponent;

	UPROPERTY(EditAnywhere, Category = "Particle")
	FTransform ParticleTransform;

	UPROPERTY(EditAnywhere, Category = "Status")
	float EnemySpeed;              //enemy speed



};
