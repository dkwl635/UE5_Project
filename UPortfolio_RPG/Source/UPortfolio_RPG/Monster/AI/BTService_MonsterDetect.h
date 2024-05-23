// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_MonsterDetect.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API UBTService_MonsterDetect : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_MonsterDetect();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
