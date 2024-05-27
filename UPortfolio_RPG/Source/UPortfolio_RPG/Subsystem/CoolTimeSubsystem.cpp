// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/CoolTimeSubsystem.h"
#include "Actors/Skill/SkillBase.h"

bool UCoolTimeSubsystem::IsSpaceCool()
{
	bool bIsSpaceCool = GetWorld()->GetTimerManager().IsTimerActive(SpaceTimer);

	return bIsSpaceCool;
}

bool UCoolTimeSubsystem::IsSkillCool(ASkillBase* Skill)
{
	if (Skill)
	{
		if (Skill->Sk_Name == TEXT("Red Dust"))
		{
			bool bIsSkillCool = GetWorld()->GetTimerManager().IsTimerActive(Skill_Q_Timer);
			return bIsSkillCool;
		}
		else if (Skill->Sk_Name == TEXT("Spinning Attack"))
		{
			bool bIsSkillCool = GetWorld()->GetTimerManager().IsTimerActive(Skill_W_Timer);
			return bIsSkillCool;
		}
		else if (Skill->Sk_Name == TEXT("신의 율법"))
		{
			bool bIsSkillCool = GetWorld()->GetTimerManager().IsTimerActive(Skill_E_Timer);
			return bIsSkillCool;
		}
		else if (Skill->Sk_Name == TEXT("Buff"))
		{
			bool bIsSkillCool = GetWorld()->GetTimerManager().IsTimerActive(Skill_R_Timer);
			return bIsSkillCool;
		}
		else
		{
			return false;
		}
	}
	else
		return false;
}

void UCoolTimeSubsystem::SetSpaceTimer()
{
	GetWorld()->GetTimerManager().SetTimer(SpaceTimer, SpaceCoolTime, false);
}

float UCoolTimeSubsystem::GetSpaceRemainingTime()
{
	return GetWorld()->GetTimerManager().GetTimerRemaining(SpaceTimer);
}

void UCoolTimeSubsystem::SetSkillTimer(ASkillBase* Skill)
{
	if (Skill)
	{
		if (Skill->Sk_Name == TEXT("Red Dust"))
		{
			GetWorld()->GetTimerManager().SetTimer(Skill_Q_Timer, Skill->Sk_CoolTime, false);
		}
		else if (Skill->Sk_Name == TEXT("Spinning Attack"))
		{
			GetWorld()->GetTimerManager().SetTimer(Skill_W_Timer, Skill->Sk_CoolTime, false);
		}
		else if (Skill->Sk_Name == TEXT("신의 율법"))
		{
			GetWorld()->GetTimerManager().SetTimer(Skill_E_Timer, Skill->Sk_CoolTime, false);
		}
		else if (Skill->Sk_Name == TEXT("Buff"))
		{
			GetWorld()->GetTimerManager().SetTimer(Skill_R_Timer, Skill->Sk_CoolTime, false);
		}
		else
		{
			return;
		}
	}
}

float UCoolTimeSubsystem::GetSkillRemainingTime(ASkillBase* Skill)
{
	if (!Skill) return 0.f;
	if (Skill->Sk_Name == TEXT("Red Dust"))
	{
		return GetWorld()->GetTimerManager().GetTimerRemaining(Skill_Q_Timer);
	}
	else if (Skill->Sk_Name == TEXT("Spinning Attack"))
	{
		return GetWorld()->GetTimerManager().GetTimerRemaining(Skill_W_Timer);
	}
	else if (Skill->Sk_Name == TEXT("신의 율법"))
	{
		return GetWorld()->GetTimerManager().GetTimerRemaining(Skill_E_Timer);
	}
	else if (Skill->Sk_Name == TEXT("Buff"))
	{
		return GetWorld()->GetTimerManager().GetTimerRemaining(Skill_R_Timer);
	}
	else
	{
		return 0.f;
	}
}