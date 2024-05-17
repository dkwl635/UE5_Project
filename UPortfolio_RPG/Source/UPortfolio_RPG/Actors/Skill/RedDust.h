// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Skill/SkillBase.h"
#include "RedDust.generated.h"

struct FSkillInfoDataTableRow;

UCLASS()
class UPORTFOLIO_RPG_API ARedDust : public ASkillBase
{
	GENERATED_BODY()
	
public:
	ARedDust();

	virtual void BeginPlay() override;

	virtual void ActiveSkill(UAnimInstance* AnimInstance) override;	

protected:
	UFUNCTION()
	void OnAttack(UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;

private:
	AActor* Owner;
};
