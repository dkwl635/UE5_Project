// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "Enemy/Enemy.h"

const FName AEnemyAIController::TargetKey(TEXT("Target"));
const FName AEnemyAIController::TargetActorKey(TEXT("TargetActor"));

AEnemyAIController::AEnemyAIController()
{
	//	RepeatInterval = 2.f;       //Ÿ�̸� �ð� 2�ʸ���

	{
		static ConstructorHelpers::FObjectFinder<UBlackboardData> Asset(TEXT("/Script/AIModule.BlackboardData'/Game/LJY/AI_NormalMonster/BBD_NormalMonsterAI.BBD_NormalMonsterAI'"));
		check(Asset.Succeeded());
		BBD = Asset.Object;
	}

	{
		static ConstructorHelpers::FObjectFinder<UBehaviorTree> Asset(TEXT("/Script/AIModule.BehaviorTree'/Game/LJY/AI_NormalMonster/BT_NormalMonsterAI.BT_NormalMonsterAI'"));
		check(Asset.Succeeded());
		BT = Asset.Object;
	}
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	check(RunBehaviorTree(BT));
}

void AEnemyAIController::OnUnPossess()
{
	Super::OnUnPossess();
	GetWorld()->GetTimerManager().ClearTimer(RepeatTimerHandle);
}

void AEnemyAIController::OnRepeatTimer()
{
	auto CurrentPawn = GetPawn();
	ensure(CurrentPawn);
	AEnemy* Enemy = Cast<AEnemy>(CurrentPawn);
	ensure(Enemy);

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld()); //���忡 ��ġ�� �� �׺�޽� �о����
	if (NavSystem == nullptr) return;

	FNavLocation NextLocation;         //AI���� �̵��� ���� ��ġ ����
	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.f, NextLocation) && !(Enemy->IsDead))
	{
		MoveToLocation(NextLocation.Location);     //AIMoveTo ���, ���� ��ġ�� �̵�
	}
}
