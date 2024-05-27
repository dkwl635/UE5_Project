// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy/UI/StatusbarUserWidget.h"
#include "Components/StatusComponent.h"
#include "Enemy/Enemy.h"
#include "Monster/Monster.h"

void UStatusbarUserWidget::SetHP(AEnemy* InEnemy)
{
	Owner = InEnemy;
	UStatusComponent* Status = InEnemy->GetStatusComponent();
	if (Status->GetMaxHP()!=0.f)
	{
		const float Percent = Status->GetCurrentHP() / Status->GetMaxHP();
		HPBar->SetPercent(Percent);
	}
}

void UStatusbarUserWidget::SetMonsterHP(AMonster* InMonster)
{
	float Status = InMonster->CurrentHP;
	if (FMath::IsNearlyZero(InMonster->MaxHP))
	{
		ensure(false);
	}
	const float Percent = Status / InMonster->MaxHP;
	HPBar->SetPercent(Percent);
}

void UStatusbarUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (Owner)
		SetHP(Owner);
	if (MonsterOwner)
		SetMonsterHP(MonsterOwner);
}
