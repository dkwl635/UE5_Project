// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BTService_Detect.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return;

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 600.f;

	if (nullptr == World) return;
	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	//플레이어 따라오게 인지하는 코드인데 오류나서 잠깐 주석처리 해놓겠습니다.
	//if (bResult)
	//{
	//	for (auto const& OverlapResult : OverlapResults)
	//	{
	//		APawn* DefaultPawn = Cast<APawn>(OverlapResult.GetActor());
	//		if (DefaultPawn)
	//		{
	//			AController* DefaultPawnController = DefaultPawn->GetController();
	//			if (DefaultPawnController && DefaultPawnController->IsPlayerController())
	//			{
	//				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetKey, DefaultPawn);
	//				FVector cCenter = DefaultPawn->GetActorLocation();
	//				UWorld* wWorld = DefaultPawn->GetWorld();
	//				if (wWorld)
	//				{
	//					// 원형 영역 디버그 그리기
	//					DrawDebugSphere(wWorld, cCenter, DetectRadius, 16, FColor::Green, false, 0.2f);
	//					// 몬스터 위치 디버그 그리기
	//					DrawDebugPoint(wWorld, ControllingPawn->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
	//					// 몬스터와 플레이어 사이에 라인 디버그 그리기
	//					DrawDebugLine(wWorld, ControllingPawn->GetActorLocation(), cCenter, FColor::Blue, false, 0.2f);
	//				}
	//				return;
	//			}
	//		}
	//	}

	//}
		DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
	
}