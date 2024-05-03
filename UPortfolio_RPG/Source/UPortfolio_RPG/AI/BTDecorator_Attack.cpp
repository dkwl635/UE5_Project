// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_Attack.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_Attack::UBTDecorator_Attack()
{
	NodeName = TEXT("CanAttack");  //데코레이트 이름
}

bool UBTDecorator_Attack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);    //공격범위에 있는지 판정

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn)
		return false;

	auto Target = Cast<APawn>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AEnemyAIController::TargetKey));
	if (nullptr == Target)
		return false;

	bResult = (Target->GetDistanceTo(ControllingPawn) <= 200.0f);
	return bResult;

}
