// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Skill/SkillBase.h"
#include "SpinningAttack.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API ASpinningAttack : public ASkillBase
{
	GENERATED_BODY()
	
public:
	ASpinningAttack();

	virtual void BeginPlay() override;

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
};
