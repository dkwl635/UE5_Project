// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyData.generated.h"

/**
 * 
 */
class Enemy;

USTRUCT()
struct UPORTFOLIO_RPG_API FEnemyData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Enemy")
	float CapsuleRadius;              //캡슐 컴포넌트 반지름

	UPROPERTY(EditAnywhere, Category = "Enemy")
	float CapsuleHalfHeight;          //캡슐 컴포넌트 반높이

	UPROPERTY(EditAnywhere, Category = "Enemy")
	USkeletalMesh* SkeletalMesh;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	FTransform SkeletalMeshTransform;   //enemy 상대적 위치

	UPROPERTY(EditAnywhere, Category = "Enemy")
	float EnemyHP;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	TSubclassOf<UAnimInstance> AnimClass;   //애니메이션

	UPROPERTY(EditAnywhere, Category = "Enemy")
	UParticleSystem* ParticleAttackSystem;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	UParticleSystemComponent* ParticleAttackSystemComponent;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	FTransform ParticleTransform;

};
