// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "CoolTimeSubsystem.generated.h"

class ASkillBase;

UCLASS()
class UPORTFOLIO_RPG_API UCoolTimeSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
	
public:
	bool IsSpaceCool();
	float GetSpaceCool() { return SpaceCoolTime; }
	void SetSpaceTimer();
	float GetSpaceRemainingTime();

public:
	bool IsSkillCool(ASkillBase* Skill);
	void SetSkillTimer(ASkillBase* Skill);
	float GetSkillRemainingTime(ASkillBase* Skill);

private:
	FTimerHandle SpaceTimer;
	FTimerHandle Skill_Q_Timer;
	FTimerHandle Skill_W_Timer;
	
private:
	float SpaceCoolTime = 5.f;

	float RemainingTime;
};