// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BTService_Detect.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/Enemy.h"
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

	FVector ZLocation = ControllingPawn->GetActorLocation();
	ZLocation.Z = 0.0f; // Z 값을 0으로 설정 //몬스터의 z값은 바닥에 고정


	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 700.f;           //�÷��̾� Ž�� ���� ������ ���ų�, ���̺�� �־�ΰڽ��ϴ�.

	if (nullptr == World) return;

	//Ÿ�� ���ͷ����̼�
	FHitResult HitResult;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);
	bool bResult = UKismetSystemLibrary::SphereTraceSingle(
		GetWorld(),
		Center,
		Center + FVector(0.f, 0.f, 1.f), // ������ ���������� �ణ ���� �������� �����Ͽ� ������ �浹�� �����մϴ�.
		DetectRadius,
		UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2),           //�浹ä��
		false, //bTraceComplex
		TArray<AActor*>(), //������ ���͵�
		EDrawDebugTrace::None, //����� Ʈ���̽�
		HitResult,
		true
	);

	//if (bResult && HitResult.GetActor() != nullptr && HitResult.GetActor()->IsA<APawn>()) //APawn�� �÷��̾�(ACharacter)�� �ٲٱ�
	//{
	//	// �÷��̾ �����Ǿ��� ���� �÷��̾ ���󰡴� ���� ����
	//	//ZLocation.Z = 0.0f; // Z 값을 0으로 설정 //몬스터의 z값은 바닥에 고정
	//	//ControllingPawn->SetActorLocation(ZLocation);
	//	APawn* TargetPawn = Cast<APawn>(HitResult.GetActor());
	//	if (TargetPawn)
	//	{
	//		// 몬스터의 위치를 캐릭터의 위치와 일정한 거리를 유지하도록 설정
	//		FVector Direction = (TargetPawn->GetActorLocation() - OwnerComp.GetOwner()->GetActorLocation()).GetSafeNormal();
	//		FVector NewLocation = TargetPawn->GetActorLocation() - Direction * 10;

	//		// 몬스터의 위치를 새로운 위치로 업데이트
	//		OwnerComp.GetOwner()->SetActorLocation(NewLocation);

	//		// 몬스터를 따라가도록 설정
	//		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetKey, TargetPawn);
	//	}
	//	//OwnerComp.GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetKey, HitResult.GetActor()); //HitResult.Player(ĳ���ͷ� �ٲٱ�)
	//	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 1.0f);
	//}
	//else
	//{
	//	// �÷��̾ �������� ������ ���� ���� ����
	//	OwnerComp.GetBlackboardComponent()->ClearValue(AEnemyAIController::TargetKey);
	//	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 1.0f);
	//}

	// vector 위치 기반
	if (bResult && HitResult.GetActor() != nullptr && HitResult.GetActor()->IsA<APawn>()) //APawn�� �÷��̾�(ACharacter)�� �ٲٱ�
	{
		// �÷��̾ �����Ǿ��� ���� �÷��̾ ���󰡴� ���� ����
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AEnemyAIController::TargetKey, HitResult.GetActor()->GetActorLocation()); //HitResult.Player(ĳ���ͷ� �ٲٱ�)
		DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 1.0f);
	}
	else
	{
		// �÷��̾ �������� ������ ���� ���� ����
		OwnerComp.GetBlackboardComponent()->ClearValue(AEnemyAIController::TargetKey);
		DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 1.0f);
	}

	
}