// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BTService_Detect.h"
#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DrawDebugHelpers.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.f; //���񽺰� �۵��ϴ� �ֱ�
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (nullptr == ControllingPawn) return;

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float DetectRadius = 600.f;           //�÷��̾� Ž�� ����

	if (nullptr == World) return;

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

	if (bResult && HitResult.GetActor() != nullptr && HitResult.GetActor()->IsA<AActor>()) //Actor�� �÷��̾�
	{
		// �÷��̾ �����Ǿ��� ���� �÷��̾ ���󰡴� ���� ����
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AEnemyAIController::TargetKey, HitResult.GetActor()); //HitResult.Player

	}
	
		DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
	
}