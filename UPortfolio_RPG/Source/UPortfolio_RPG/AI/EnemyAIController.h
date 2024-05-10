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
	virtual void OnPossess(APawn* InPawn) override;  //��Ʈ�ѷ� ����
	virtual void OnUnPossess() override;			 //���� ����

public:
	static const FName TargetKey;
	static const FName TargetActorKey;

private:
	void OnRepeatTimer();

	FTimerHandle RepeatTimerHandle;   //Ÿ�̸�
	float RepeatInterval;

	UPROPERTY()
		class UBehaviorTree* BT;

	UPROPERTY()
		class UBlackboardData* BBD;
};
