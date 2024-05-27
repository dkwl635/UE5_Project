//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "Monster/AI/BTDecorator_Random.h"
//#include "BehaviorTree/BlackboardComponent.h"
//#include "Monster/AI/MonsterAIController.h"
//
//UBTDecorator_Random::UBTDecorator_Random()
//{
//	////NodeName = "RandomDecorator";
//}
//
//bool UBTDecorator_Random::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
//{
//    //// 랜덤으로 확률을 계산
//    //float RandomValue = FMath::FRandRange(0.f, 1.f);
//
//    //// 블랙보드 컴포넌트에서 확률 값을 가져옴
//    //UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
//    //if (BlackboardComp == nullptr)
//    //{
//    //    return false;
//    //}
//
//    //// 데코레이터가 사용할 블랙보드 키의 이름 설정
//    //FName BlackboardKey = GetSelectedBlackboardKey();
//
//    //// 블랙보드에서 확률 값 가져오기
//    //float Probability;
//    //if (!BlackboardComp->GetValueAsFloat(BlackboardKey, Probability))
//    //{
//    //    return false;
//    //}
//
//    //// 랜덤 값이 확률보다 작으면 true 반환하여 자식 노드를 실행
//    //return RandomValue <= Probability;
//}
