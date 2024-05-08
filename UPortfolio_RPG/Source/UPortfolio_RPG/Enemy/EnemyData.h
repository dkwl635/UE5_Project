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

	UPROPERTY()
	float CapsuleRadius;              //캡슐 컴포넌트 반지름

	UPROPERTY()
	float CapsuleHalfHeight;          //캡슐 컴포넌트 반높이

	UPROPERTY()
	USkeletalMesh* SkeletalMesh;

	UPROPERTY()
	FTransform SkeletalMeshTransform;   //enemy 상대적 위치

	UPROPERTY()
	float EnemyHP;

	UPROPERTY()
	TSubclassOf<UAnimInstance> AnimClass;   //애니메이션

};
