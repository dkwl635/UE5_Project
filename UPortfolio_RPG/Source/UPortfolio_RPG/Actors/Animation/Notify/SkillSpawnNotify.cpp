// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Animation/Notify/SkillSpawnNotify.h"
#include "Actors/Skill/SkillBase.h"

void USkillSpawnNotify::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration,EventReference);

    if (MeshComp && MeshComp->GetOwner()&&SkillActorClass)
    {
        UWorld* World = MeshComp->GetOwner()->GetWorld();
        if (World)
        {
            // Actor Spawn Location & Rotation
            FVector Location = MeshComp->GetOwner()->GetActorLocation();
            FRotator Rotation = MeshComp->GetOwner()->GetActorRotation();

            // Spawning Actor Class
            SpawnActor = World->SpawnActor<ASkillBase>(SkillActorClass, Location, Rotation);
        }
    }
}

void USkillSpawnNotify::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    if (MeshComp && MeshComp->GetOwner())
    {
        UWorld* World = MeshComp->GetOwner()->GetWorld();
        if (World)
        {
            if(SpawnActor)
            {
                World->DestroyActor(SpawnActor);
                SpawnActor = nullptr;
            }
        }
    }
	Super::NotifyEnd(MeshComp, Animation,EventReference);
}
