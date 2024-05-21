// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MonsterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API UMonsterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UMonsterAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsScream;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsDetach;
	
};
