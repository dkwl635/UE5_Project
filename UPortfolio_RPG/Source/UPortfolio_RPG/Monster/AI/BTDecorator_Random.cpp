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
//    //// �������� Ȯ���� ���
//    //float RandomValue = FMath::FRandRange(0.f, 1.f);
//
//    //// ������ ������Ʈ���� Ȯ�� ���� ������
//    //UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
//    //if (BlackboardComp == nullptr)
//    //{
//    //    return false;
//    //}
//
//    //// ���ڷ����Ͱ� ����� ������ Ű�� �̸� ����
//    //FName BlackboardKey = GetSelectedBlackboardKey();
//
//    //// �����忡�� Ȯ�� �� ��������
//    //float Probability;
//    //if (!BlackboardComp->GetValueAsFloat(BlackboardKey, Probability))
//    //{
//    //    return false;
//    //}
//
//    //// ���� ���� Ȯ������ ������ true ��ȯ�Ͽ� �ڽ� ��带 ����
//    //return RandomValue <= Probability;
//}
