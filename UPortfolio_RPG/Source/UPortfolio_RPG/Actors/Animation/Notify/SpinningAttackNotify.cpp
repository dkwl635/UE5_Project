// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Animation/Notify/SpinningAttackNotify.h"
#include "Actors/Skill/SpinningAttack.h"

void USpinningAttackNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration,EventReference);

    if (MeshComp && MeshComp->GetOwner())
    {
        UWorld* World = MeshComp->GetOwner()->GetWorld();
        if (World)
        {
            // Actor Spawn Location & Rotation
            FVector Location = MeshComp->GetOwner()->GetActorLocation();
            FRotator Rotation = MeshComp->GetOwner()->GetActorRotation();

            // Spawning Actor Class
            TSubclassOf<AActor> ActorToSpawn = ASpinningAttack::StaticClass();

            // Spawn Actor
            SpawnActor = World->SpawnActor<AActor>(ActorToSpawn, Location, Rotation);
        }
    }
}

void USpinningAttackNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    if (MeshComp && MeshComp->GetOwner())
    {
        UWorld* World = MeshComp->GetOwner()->GetWorld();
        if (World)
        {
            World->DestroyActor(SpawnActor);
        }
    }
	Super::NotifyEnd(MeshComp, Animation,EventReference);
}
