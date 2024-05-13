// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Skill/SpaceCoolTimerWidget.h"
#include "Actors/Controller/BasicPlayerController.h"
#include "Subsystem/CoolTimeSubsystem.h"
#include "Kismet/GameplayStatics.h"

void USpaceCoolTimerWidget::SetProgressBar()
{
	Super::SetProgressBar();

	ABasicPlayerController* PlayerController =
		Cast<ABasicPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!PlayerController) return;

	UCoolTimeSubsystem* Manager = PlayerController->GetCoolTimeManager();
	if (!Manager) return;
	RemainingTime = Manager->GetSpaceRemainingTime();

	MaxTime = Manager->GetSpaceCool();

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
