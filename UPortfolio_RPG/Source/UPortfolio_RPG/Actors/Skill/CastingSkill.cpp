// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Skill/CastingSkill.h"

ACastingSkill::ACastingSkill()
{
	TargetingCircleInstance = nullptr;

    {
        static ConstructorHelpers::FClassFinder<AActor> EffectActor(TEXT("/Script/Engine.Blueprint'/Game/KSH/Character/Skill/SpawnedActor/EffectActor.EffectActor_C'"));
        ensure(EffectActor.Class);
        AreaEffectActor = EffectActor.Class;
    }
    {
        static ConstructorHelpers::FObjectFinder<UAnimMontage> Asset(TEXT("/Script/Engine.AnimMontage'/Game/KSH/Character/Animation/Skill/CastingSkill_Montage.CastingSkill_Montage'"));
        ensure(Asset.Object);
        this->Montage = Asset.Object;
    }
    {
        static ConstructorHelpers::FObjectFinder<UTexture2D> Asset(TEXT("/Script/Engine.Texture2D'/Game/KSH/Character/Skill/Icon/CastingSkill.CastingSkill'"));
        ensure(Asset.Object);
        this->Sk_Image = Asset.Object;
    }
    {
        static ConstructorHelpers::FObjectFinder<UTexture2D> Asset(TEXT("/Script/Engine.Texture2D'/Game/KSH/Character/Skill/Icon/CastingSkillDark.CastingSkillDark'"));
        ensure(Asset.Object);
        this->Sk_Image_Cool = Asset.Object;
    }

    Sk_Name = TEXT("신의 율법");
    Sk_Desc = FText::FromString(TEXT("빛의 마법진을 소환한다."));
    Sk_CoolTime = 10.f;
    Sk_Damage = 70.f;
    Sk_ManaUsage = 20.f;
    Sk_MaxDistance = 1500.f;
}

void ACastingSkill::BeginPlay()
{
	Super::BeginPlay();

}

void ACastingSkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACastingSkill::ActiveSkill(UAnimInstance* AnimInstance)
{
    if(CurrentSkillState == ESkillState::Idle)
    {
        StartTargeting();
    }
    else
    {
        Super::ActiveSkill(AnimInstance);

        CastAreaEffect();
        ApplyDamage();
    }
}

#include "Kismet/GameplayStatics.h"
#include "Actors/PlayerCharacter/PlayerCharacter.h"
#include "Enemy/Enemy.h"
#include "Engine/DamageEvents.h"
void ACastingSkill::ApplyDamage()
{
    TArray<AActor*> OverlappingActors;
    AreaEffecInstance->GetOverlappingActors(OverlappingActors);
    
    for (auto& It : OverlappingActors)
    {
        if (AEnemy* Enemy = Cast<AEnemy>(It))
        {
            if (APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
            {
                float Damage = FMath::RandRange(Player->GetStatusComponent()->GetMinAttackDamage(), Player->GetStatusComponent()->GetMaxAttackDamage());
                Damage += Sk_Damage;
                FDamageEvent Event;
                Enemy->TakeDamage(Damage, Event, Player->GetController(), Player);
            }
        }
    }
}

FVector ACastingSkill::GetMouseWorldPosition()
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        float MouseX, MouseY;
        PlayerController->GetMousePosition(MouseX, MouseY);

        FVector WorldLocation, WorldDirection;
        PlayerController->DeprojectScreenPositionToWorld(MouseX, MouseY, WorldLocation, WorldDirection);

        FHitResult HitResult;
        FVector Start = WorldLocation;
        FVector End = Start + (WorldDirection * 10000.0f);

        if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility))
        {
            return HitResult.Location;
        }
    }

    return FVector::ZeroVector;
}

void ACastingSkill::StartTargeting()
{
    CurrentSkillState = ESkillState::Targeting;
}

void ACastingSkill::CastAreaEffect()
{
    APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    AActor* TargetingCircle = Player->GetTargetingActor();

    if (TargetingCircle && AreaEffectActor)
    {
        FVector TargetPosition = TargetingCircle->GetActorLocation() + FVector(0, 0, 30);
        AreaEffecInstance = GetWorld()->SpawnActor<AActor>(AreaEffectActor, TargetPosition, FRotator::ZeroRotator);

        CurrentSkillState = ESkillState::Idle;
    }
}
