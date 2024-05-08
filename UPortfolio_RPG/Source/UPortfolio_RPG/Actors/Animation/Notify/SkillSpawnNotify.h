// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SkillSpawnNotify.generated.h"

class ASkillBase;

UCLASS()
class UPORTFOLIO_RPG_API USkillSpawnNotify : public UAnimNotifyState
{
	GENERATED_BODY()

protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill")
	TSubclassOf<ASkillBase> SkillActorClass;
private:
	ASkillBase* SpawnActor;
};
