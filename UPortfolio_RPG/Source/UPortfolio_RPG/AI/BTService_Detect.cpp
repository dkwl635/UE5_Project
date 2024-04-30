// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BTService_Detect.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.f; //서비스가 작동하는 주기
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return;

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 600.f;           //플레이어 탐지 범위

	if (nullptr == World) return;

	FHitResult HitResult;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = UKismetSystemLibrary::SphereTraceSingle(
		GetWorld(),
		Center,
		Center + FVector(0.f, 0.f, 1.f), // 끝점을 시작점에서 약간 높은 지점으로 설정하여 땅과의 충돌을 방지합니다.
		DetectRadius,
		UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2),           //충돌채널
		false, //bTraceComplex
		TArray<AActor*>(), //무시할 액터들
		EDrawDebugTrace::None, //디버그 트레이스
		HitResult,
		true
	);

	if (bResult && HitResult.GetActor() != nullptr && HitResult.GetActor()->IsA<AActor>()) //Actor는 플레이어
	{
		// 플레이어가 감지되었을 때의 플레이어를 따라가는 동작 수행
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetKey, HitResult.GetActor()); //HitResult.Player

	}
	
		DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
	
}