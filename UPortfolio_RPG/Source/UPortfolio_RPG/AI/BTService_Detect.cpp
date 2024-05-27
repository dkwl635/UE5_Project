// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BTService_Detect.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/Enemy.h"
#include "Actors/PlayerCharacter/PlayerCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 0.5f; //���񽺰� �۵��ϴ� �ֱ�
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn(); 
	if (nullptr == ControllingPawn) return;

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 2000.f;           //감지 반경

	if (nullptr == World) return;

	//감지 확인
	FHitResult HitResult;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = UKismetSystemLibrary::SphereTraceSingle(
		GetWorld(),
		Center,
		Center + FVector(0.f, 0.f, 1.f), // ������ ���������� �ణ ���� �������� �����Ͽ� ������ �浹�� �����մϴ�.
		DetectRadius,
		UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel12),           //�浹ä��
		false, //bTraceComplex
		TArray<AActor*>(), //������ ���͵�
		EDrawDebugTrace::None, //����� Ʈ���̽�
		HitResult,
		true
	);
	auto Enemy = Cast<AEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (bResult && HitResult.GetActor() != nullptr && HitResult.GetActor()->IsA<APawn>()) //APawn�� �÷��̾�(ACharacter)�� �ٲٱ�
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetActorKey, HitResult.GetActor()); //HitResult.Player(ĳ���ͷ� �ٲٱ�)
	//	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 1.0f);
	}
	else
	{
		// �÷��̾ �������� ������ ���� ���� ����
		OwnerComp.GetBlackboardComponent()->ClearValue(AEnemyAIController::TargetActorKey);
		//DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 1.0f);

	}

	//// vector 위치 기반
	//if (bResult && HitResult.GetActor() != nullptr && HitResult.GetActor()->IsA<APawn>()) //APawn�� �÷��̾�(ACharacter)�� �ٲٱ�
	//{
	//	// �÷��̾ �����Ǿ��� ���� �÷��̾ ���󰡴� ���� ����
	//	OwnerComp.GetBlackboardComponent()->SetValueAsVector(AEnemyAIController::TargetKey, HitResult.GetActor()->GetActorLocation()); //HitResult.Player(ĳ���ͷ� �ٲٱ�)
	//	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 1.0f);
	//}
	//else
	//{
	//	// �÷��̾ �������� ������ ���� ���� ����
	//	OwnerComp.GetBlackboardComponent()->ClearValue(AEnemyAIController::TargetKey);
	//	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 1.0f);
	//}

	
}