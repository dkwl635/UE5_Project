// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/SpaceCoolTimerWidget.h"
#include "Actors/PlayerCharacter/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void USpaceCoolTimerWidget::SetProgressBar()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PlayerController) return;

	APlayerCharacter* Player = Cast<APlayerCharacter>(PlayerController->GetCharacter());
	if (!Player) return;

	FTimerHandle CoolTimer = Player->GetTimerHandle();
	float RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(CoolTimer);
	float MaxTime = Player->GetSpaceCoolTime();

	if (MaxTime > 0) // 0으로 나누는 것을 방지
	{
		float Percent = RemainingTime / MaxTime;
		ProgressBar->SetPercent(Percent);
	}

	// 남은 시간을 표시 (소수점 아래는 표시하지 않기 위해 FMath::FloorToInt를 사용하여 정수로 변환)
	FText RemainingTimeText = FText::AsNumber(FMath::FloorToInt(RemainingTime));
	TextBlock->SetText(RemainingTimeText);
}
