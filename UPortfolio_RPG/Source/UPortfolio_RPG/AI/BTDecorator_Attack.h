// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// +character.h
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_Attack.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API UBTDecorator_Attack : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_Attack();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
