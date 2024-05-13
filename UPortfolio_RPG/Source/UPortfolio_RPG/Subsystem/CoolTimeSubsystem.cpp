// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/CoolTimeSubsystem.h"

bool UCoolTimeSubsystem::IsSpaceCool()
{
	bool bIsSpaceCool = GetWorld()->GetTimerManager().IsTimerActive(SpaceTimer);

	return bIsSpaceCool;
}

void UCoolTimeSubsystem::SetSpaceTimer()
{
	GetWorld()->GetTimerManager().SetTimer(SpaceTimer, SpaceCoolTime, false);
}

float UCoolTimeSubsystem::GetSpaceRemainingTime()
{
	return GetWorld()->GetTimerManager().GetTimerRemaining(SpaceTimer);
}
