// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

const FName AEnemyAIController::TargetKey(TEXT("Target"));

AEnemyAIController::AEnemyAIController()
{
	//	RepeatInterval = 2.f;       //타이머 시간 2초마다

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

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld()); //월드에 배치해 둔 네비메쉬 읽어오기
	if (NavSystem == nullptr) return;

	FNavLocation NextLocation;         //AI폰이 이동할 다음 위치 저장
	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.f, NextLocation)) 
	{
		MoveToLocation(NextLocation.Location);     //AIMoveTo 노드, 다음 위치로 이동
	}
}
