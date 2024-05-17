// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Skill/SkillBase.h"
#include "Actors/PlayerCharacter/PlayerCharacter.h"
#include "Components/StatusComponent.h"

void ASkillBase::ActiveSkill(UAnimInstance* AnimInstance)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (Player->GetStatusComponent()->GetCurrentMP() < Sk_ManaUsage)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Enough Mana"));
		return;
	}
	else
	{
		float MP = Player->GetStatusComponent()->GetCurrentMP() - Sk_ManaUsage;
		Player->GetStatusComponent()->SetCurrentMP(MP);
	}
	if(Montage)
		AnimInstance->Montage_Play(Montage, 1.2f);
}