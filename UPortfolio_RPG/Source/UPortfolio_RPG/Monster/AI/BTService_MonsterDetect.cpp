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
	
//		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AMonsterAIController::TargetKey, ); 
		
}
