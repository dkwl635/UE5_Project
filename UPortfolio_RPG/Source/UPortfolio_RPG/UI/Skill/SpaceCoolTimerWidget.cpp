// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Skill/SpaceCoolTimerWidget.h"
#include "Actors/PlayerCharacter/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void USpaceCoolTimerWidget::SetProgressBar()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PlayerController) return;

	APlayerCharacter* Player = Cast<APlayerCharacter>(PlayerController->GetCharacter());
	if (!Player) return;

	FTimerHandle CoolTimer = Player->GetTimerHandle();
	RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(CoolTimer);
	float MaxTime = Player->GetSpaceCoolTime();

	if (MaxTime > 0.f)
	{
		float Percent = RemainingTime / MaxTime;
		ProgressBar->SetPercent(Percent);
	}

	FNumberFormattingOptions NumberFormatOptions;
	NumberFormatOptions.MinimumFractionalDigits = 1;
	NumberFormatOptions.MaximumFractionalDigits = 1;

	FText RemainingTimeText = FText::Format(NSLOCTEXT("YourNamespace", "YourKey", "{0}"), FText::AsNumber(RemainingTime, &NumberFormatOptions));
	TextBlock->SetText(RemainingTimeText);
}
