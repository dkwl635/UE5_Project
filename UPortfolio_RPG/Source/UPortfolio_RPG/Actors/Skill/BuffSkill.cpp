// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Skill/BuffSkill.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/PlayerCharacter/PlayerCharacter.h"
#include "Components/StatusComponent.h"


ABuffSkill::ABuffSkill()
{
    {
        static ConstructorHelpers::FObjectFinder<UAnimMontage> Asset(TEXT("/Script/Engine.AnimMontage'/Game/KSH/Character/Animation/Skill/BuffSkill_Montage.BuffSkill_Montage'"));
        ensure(Asset.Object);
        this->Montage = Asset.Object;
    }
    {
        static ConstructorHelpers::FObjectFinder<UTexture2D> Asset(TEXT("/Script/Engine.Texture2D'/Game/KSH/Character/Skill/Icon/BuffSkill.BuffSkill'"));
        ensure(Asset.Object);
        this->Sk_Image = Asset.Object;
    }
    {
        static ConstructorHelpers::FObjectFinder<UTexture2D> Asset(TEXT("/Script/Engine.Texture2D'/Game/KSH/Character/Skill/Icon/BuffSkillDark.BuffSkillDark'"));
        ensure(Asset.Object);
        this->Sk_Image_Cool = Asset.Object;
    }
    {
        static ConstructorHelpers::FClassFinder<AActor> EffectActorAsset(TEXT("/Script/Engine.Blueprint'/Game/KSH/Character/Skill/SpawnedActor/BuffEffectActor.BuffEffectActor_C'"));
        ensure(EffectActorAsset.Class);
        EffectActor = EffectActorAsset.Class;
    }
    
    Sk_Name = TEXT("Buff");
    Sk_CoolTime = 12.f;
    Sk_Desc = FText::FromString(TEXT("6초 동안 공격력을 50% 올려준다"));
    Sk_Damage = 0.5f;
    Sk_ManaUsage = 50.f;
    Sk_MaxDistance = 0.f;
}

void ABuffSkill::ActiveSkill(UAnimInstance* AnimInstance)
{
    Super::ActiveSkill(AnimInstance);

    SetBuffTimer();

    APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    if (Player)
    {
        CachedDamage = Player->GetStatusComponent()->GetAttackDamage();
        FVector Location = Player->GetActorLocation();
        FRotator Rotation = Player->GetActorRotation();
        EffectActorInstance = GetWorld()->SpawnActor<AActor>(EffectActor, Location, Rotation);
        Player->GetStatusComponent()->SetAttackDamage(CachedDamage * 1.5f);
        FAttachmentTransformRules Rules(EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, EAttachmentRule::KeepWorld, false);
        EffectActorInstance->AttachToActor(Player, Rules);
    }
}

void ABuffSkill::SetBuffTimer()
{
    GetWorld()->GetTimerManager().SetTimer(BuffTimer, this, &ABuffSkill::OnEndBuff, BuffTime, false);
}

void ABuffSkill::OnEndBuff()
{
    APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    if (Player)
    {
        Player->GetStatusComponent()->SetAttackDamage(CachedDamage);
    }
    GetWorld()->GetTimerManager().ClearTimer(BuffTimer);
}
