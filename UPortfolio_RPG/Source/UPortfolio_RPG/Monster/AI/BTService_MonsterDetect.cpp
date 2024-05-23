// Fill out your copyright notice in the Description page of Project Settings.

#include "Monster/AI/BTService_MonsterDetect.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Monster/AI/MonsterAIController.h"
#include "Actors/PlayerCharacter/PlayerCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include"Monster/Monster.h"


UBTService_MonsterDetect::UBTService_MonsterDetect()
{
	NodeName = TEXT("MonsterDetect");
	Interval = 1.0f; 
}

void UBTService_MonsterDetect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
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
		Center + FVector(0.f, 0.f, 1.f), 
		DetectRadius,
		UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2),           
		false, //bTraceComplex
		TArray<AActor*>(), 
		EDrawDebugTrace::None, 
		HitResult,
		true
	);
	auto Enemy = Cast<AMonster>(OwnerComp.GetAIOwner()->GetPawn());
	if (bResult && HitResult.GetActor() != nullptr && HitResult.GetActor()->IsA<APawn>()) 
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AMonsterAIController::TargetKey, HitResult.GetActor()); 
			DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 1.0f);
	}
	else
	{
		
		OwnerComp.GetBlackboardComponent()->ClearValue(AMonsterAIController::TargetKey);
			DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 1.0f);

	}
}
