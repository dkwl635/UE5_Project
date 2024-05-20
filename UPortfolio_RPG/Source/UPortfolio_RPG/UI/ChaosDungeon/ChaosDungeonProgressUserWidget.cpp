// Fill out your copyright notice in the Description page of Project Settings.


#include "ChaosDungeonProgressUserWidget.h"
#include "Subsystem/ChaosDungeon/ChaosDungeonSubsystem.h"
#include "Kismet/GameplayStatics.h"

void UChaosDungeonProgressUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	EscapeButton->OnPressed.AddDynamic(this, &UChaosDungeonProgressUserWidget::OnPressButton);
}

void UChaosDungeonProgressUserWidget::SetProgress()
{
	if (GetWorld())
	{
		if (UChaosDungeonSubsystem* Subsystem = GetWorld()->GetSubsystem<UChaosDungeonSubsystem>())
		{
			const float CurPurification = Subsystem->GetPurification();
			const float MaxPurification = 20000;

			const float Percent = CurPurification / MaxPurification;
			if(ProgressBar)
				ProgressBar->SetPercent(Percent);

			FString PercentageText = FString::Printf(TEXT("%d%%"), static_cast<int32>(Percent * 100));
			if(PercentageTextBlock)
				PercentageTextBlock->SetText(FText::FromString(PercentageText));
		}
	}
}

void UChaosDungeonProgressUserWidget::OnPressButton()
{
	UGameplayStatics::OpenLevel(this, FName(TEXT("KSHTestMap")));
}
