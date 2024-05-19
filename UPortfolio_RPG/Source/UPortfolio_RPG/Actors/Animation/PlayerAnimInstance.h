// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"


UCLASS()
class UPORTFOLIO_RPG_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPlayerAnimInstance();

protected:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	double Speed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsSpace;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float HP;

private:
	ACharacter* Character;
};
