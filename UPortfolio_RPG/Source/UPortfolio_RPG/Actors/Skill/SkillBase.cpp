// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Skill/SkillBase.h"

float ASkillBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}