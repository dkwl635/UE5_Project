// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Skill/SkillBase.h"
#include "CastingSkill.generated.h"

UCLASS()
class UPORTFOLIO_RPG_API ACastingSkill : public ASkillBase
{
	GENERATED_BODY()
	
public:
    ACastingSkill();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

public:
    virtual void ActiveSkill(UAnimInstance* AnimInstance) override;
    void ApplyDamage();

protected:
    UPROPERTY(EditAnywhere, Category = "Skill")
    TSubclassOf<AActor> TargetingCircleActor;

    UPROPERTY(EditAnywhere, Category = "Skill")
    TSubclassOf<AActor> AreaEffectActor;

    AActor* TargetingCircleInstance;
    AActor* AreaEffecInstance;

    FVector GetMouseWorldPosition();
    void StartTargeting();
    void CastAreaEffect();
};
