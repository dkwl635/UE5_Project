// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/MonsterAIController.h"

const FName AMonsterAIController::TargetKey(TEXT("TargetActor"));

AMonsterAIController::AMonsterAIController()
{
	{
		static ConstructorHelpers::FObjectFinder<UBlackboardData> Asset(TEXT("/Script/AIModule.BlackboardData'/Game/LJY/BossMonster/AI/BBD_Monster.BBD_Monster'"));
		check(Asset.Succeeded());
		BBD = Asset.Object;
	}

	{
		static ConstructorHelpers::FObjectFinder<UBehaviorTree> Asset(TEXT("/Script/AIModule.BehaviorTree'/Game/LJY/BossMonster/AI/BT_Monster.BT_Monster'"));
		check(Asset.Succeeded());
		BT = Asset.Object;
	}
}

void AMonsterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (!RunBehaviorTree(BT))
	{
		UE_LOG(LogTemp, Warning, TEXT("BT Not Run!!"));
	}
}

void AMonsterAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
