// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */


UCLASS()
class UPORTFOLIO_RPG_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
public:
	AEnemyAIController();
	virtual void OnPossess(APawn* InPawn) override;  //컨트롤러 빙의
	virtual void OnUnPossess() override;			 //빙의 해제

public:
	static const FName TargetKey;

private:
	void OnRepeatTimer();

	FTimerHandle RepeatTimerHandle;   //타이머
	float RepeatInterval;

	UPROPERTY()
		class UBehaviorTree* BT;

	UPROPERTY()
		class UBlackboardData* BBD;
};
