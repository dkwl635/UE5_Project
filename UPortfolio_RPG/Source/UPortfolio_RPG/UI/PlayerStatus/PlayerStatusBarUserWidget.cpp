// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerStatus/PlayerStatusBarUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Controller/BasicPlayerController.h"
#include "Actors/PlayerCharacter/PlayerCharacter.h"
#include "Components/StatusComponent.h"

void UPlayerStatusBarUserWidget::SetHPBar()
{
	ABasicPlayerController* PlayerController =
		Cast<ABasicPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!PlayerController) return;
	APlayerCharacter* Player = Cast<APlayerCharacter>(PlayerController->GetPawn());
	if (!Player) return;
	UStatusComponent* Status = Player->GetStatusComponent();
	if (!Status) return;

	float MaxHP = Status->GetMaxHP();
	float CurrentHP = Status->GetCurrentHP();

	if (MaxHP > 0.f)
	{
		float Percent = CurrentHP / MaxHP;
		ProgressBar->SetPercent(Percent);
	}

	MaxStatusTextBlock->SetText(FText::AsNumber(MaxHP));
	CurrentStatusTextBlock->SetText(FText::AsNumber(CurrentHP));
}

void UPlayerStatusBarUserWidget::SetMPBar()
{
	ABasicPlayerController* PlayerController =
		Cast<ABasicPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!PlayerController) return;
	APlayerCharacter* Player = Cast<APlayerCharacter>(PlayerController->GetPawn());
	if (!Player) return;
	UStatusComponent* Status = Player->GetStatusComponent();
	if (!Status) return;

	float MaxMP = Status->GetMaxMP();
	float CurrentMP = Status->GetCurrentMP();

	if (MaxMP > 0.f)
	{
		float Percent = CurrentMP / MaxMP;
		ProgressBar->SetPercent(Percent);
	}

	MaxStatusTextBlock->SetText(FText::AsNumber(MaxMP));
	CurrentStatusTextBlock->SetText(FText::AsNumber(CurrentMP));
}
