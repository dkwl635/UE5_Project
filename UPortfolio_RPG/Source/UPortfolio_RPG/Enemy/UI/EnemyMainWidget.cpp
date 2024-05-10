// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/UI/EnemyMainWidget.h"

void UEnemyMainWidget::SetHP(const float CurrentHP, const float MaxHP)
{
	EnemyStatusBar->SetHP(CurrentHP, MaxHP);
}
