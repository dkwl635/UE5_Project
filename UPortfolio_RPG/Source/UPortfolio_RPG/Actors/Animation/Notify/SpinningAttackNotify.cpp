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
            // 액터 스폰 위치와 회전 정의
            FVector Location = MeshComp->GetOwner()->GetActorLocation();
            FRotator Rotation = MeshComp->GetOwner()->GetActorRotation();

            // 스폰할 액터 클래스 지정
            TSubclassOf<AActor> ActorToSpawn = ASpinningAttack::StaticClass();

            // 액터 스폰
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
