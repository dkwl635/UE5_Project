// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Skill/SkillBase.h"
#include "CastingSkill.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API ACastingSkill : public ASkillBase
{
	GENERATED_BODY()
	
protected:
    // 현재 스킬 상태
    ESkillState CurrentSkillState;

    // 타겟팅 서클
    UPROPERTY(EditAnywhere, Category = "Skill")
    TSubclassOf<AActor> TargetingCircleActor;

    // 광역 공격 이펙트
    UPROPERTY(EditAnywhere, Category = "Skill")
    TSubclassOf<AActor> AreaEffectActor;

    // 타겟팅 서클 인스턴스
    AActor* TargetingCircleInstance;

    // 타겟 위치를 얻기 위한 함수
    FVector GetMouseWorldPosition();

    // 스킬 키 입력 처리 함수
    void HandleSkillKeyInput();

    // 타겟팅 시작
    void StartTargeting();

    // 광역 공격 시전
    void CastAreaEffect();
};
