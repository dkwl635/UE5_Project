// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Skill/SkillBase.h"
#include "BuffSkill.generated.h"

class UParticleSystemComponent;
class UParticleSystem;

UCLASS()
class UPORTFOLIO_RPG_API ABuffSkill : public ASkillBase
{
	GENERATED_BODY()
	
public:
	ABuffSkill();

	virtual void ActiveSkill(UAnimInstance* AnimInstance) override;
	
protected:
	void SetBuffTimer();
	UFUNCTION()
	void OnEndBuff();
protected:
	UPROPERTY()
	TSubclassOf<AActor> EffectActor;

	AActor* EffectActorInstance = nullptr;

private:
	FTimerHandle BuffTimer;
	const float BuffTime = 6.f;

	float CachedDamage = 0.f;
};
