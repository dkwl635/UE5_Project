// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Enemy/UI/StatusbarUserWidget.h"
#include "EnemyMainWidget.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API UEnemyMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
//public:
//	void SetHP(const float CurrentHP, const float MaxHP);

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UStatusbarUserWidget* EnemyStatusBar;
};