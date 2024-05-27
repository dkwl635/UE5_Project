// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_Attack.h"
#include "EnemyAIController.h"
#include "Enemy/Enemy.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_Attack::UBTDecorator_Attack()
{
	NodeName = TEXT("CanAttack");  //데코레이트 이름
}

bool UBTDecorator_Attack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);    //공격범위에 있는지 판정

	AEnemy* ControllingPawn = Cast<AEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == ControllingPawn)
		return false;
	if (ControllingPawn->IsDead)
		return false;

	// 액터기반
	auto Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AEnemyAIController::TargetActorKey));
	if (nullptr == Target)
		return false;

	bResult = (Target->GetDistanceTo(ControllingPawn) <= 200.0f);
	UE_LOG(LogTemp, Warning, TEXT("bResult: %d"), bResult);
	return bResult;

	/*FVector TargetVector = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AEnemyAIController::TargetKey);
	{
		FVector ControllingPawnLocation = ControllingPawn->GetActorLocation();
		float DistanceSquared = FVector::DistSquared(TargetVector, ControllingPawnLocation);
		bResult = (DistanceSquared <= 200.0f * 200.0f); 
	}
	return bResult;*/
}
