// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Animation/Notify/AttackAnimNotify.h"
#include "Actors/PlayerCharacter/PlayerCharacter.h"

void UAttackAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	AActor* Actor = MeshComp->GetOwner();
	APlayerCharacter* Character = Cast<APlayerCharacter>(Actor);
	ensure(Character);
	Character->DefaultAttackCheck();
}
