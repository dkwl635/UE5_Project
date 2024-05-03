// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Animation/Notify/ComboAnimNotifyState.h"
#include "Actors/PlayerCharacter/PlayerCharacter.h"

void UComboAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	if (APlayerCharacter* Player = Cast<APlayerCharacter>(MeshComp->GetOwner()))
	{
		Player->CurrentMontage = NextMontage;
		Player->bOnAttack = false;
	}
}

void UComboAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (APlayerCharacter* Player = Cast<APlayerCharacter>(MeshComp->GetOwner()))
	{
		if(Player->bOnAttack)
			Player->CurrentMontage = Player->AttackAMontage;
	}
}