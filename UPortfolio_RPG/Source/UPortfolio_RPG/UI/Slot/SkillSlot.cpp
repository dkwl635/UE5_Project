// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Slot/SkillSlot.h"
#include "Actors/Controller/BasicPlayerController.h"
#include "Actors/PlayerCharacter/PlayerCharacter.h"
#include "Components/SkillComponent.h"
#include "Actors/Skill/SkillBase.h"
#include "Subsystem/CoolTimeSubsystem.h"
#include "Kismet/GameplayStatics.h"

void USkillSlot::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	SetProgressBar();
}

void USkillSlot::SetProgressBar()
{
	Super::SetProgressBar();

	ABasicPlayerController* PlayerController =
		Cast<ABasicPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!PlayerController) return;
	APlayerCharacter* Player = Cast<APlayerCharacter>(PlayerController->GetPawn());

	UCoolTimeSubsystem* Manager = PlayerController->GetCoolTimeManager();
	if (!Manager) return;
	if(CachedSkill)
	{
		RemainingTime = Manager->GetSkillRemainingTime(CachedSkill);
		MaxTime = CachedSkill->Sk_CoolTime;

		if (MaxTime > 0.f)
		{
			float Percent = RemainingTime / MaxTime;
			ProgressBar->SetPercent(Percent);
		}

		FNumberFormattingOptions NumberFormatOptions;
		NumberFormatOptions.MinimumFractionalDigits = 1;
		NumberFormatOptions.MaximumFractionalDigits = 1;

		FText RemainingTimeText = FText::Format(NSLOCTEXT("YourNamespace", "YourKey", "{0}"), FText::AsNumber(RemainingTime, &NumberFormatOptions));
		if (RemainingTime > 0.f)
			TextBlock->SetText(RemainingTimeText);
		else
			TextBlock->SetText(FText::GetEmpty());
	}
}

void USkillSlot::SetCachedSkill(int32 Index)
{
	ABasicPlayerController* PlayerController =
		Cast<ABasicPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!PlayerController) return;
	APlayerCharacter* Player = Cast<APlayerCharacter>(PlayerController->GetPawn());
	TArray<ASkillBase*> Skill = Player->GetSkillComponent()->GetSkills();
	if (Skill.Num() <= Index)
		CachedSkill = nullptr;
	else
		CachedSkill = Skill[Index];

	if (CachedSkill)
	{
		FProgressBarStyle Style = ProgressBar->GetWidgetStyle();
		FSlateBrush BackgroundBrush;
		BackgroundBrush.SetResourceObject(CachedSkill->Sk_Image);
		Style.BackgroundImage = BackgroundBrush;

		// 채우기 이미지 설정
		FSlateBrush FillBrush;
		FillBrush.SetResourceObject(CachedSkill->Sk_Image_Cool);
		Style.FillImage = FillBrush;

		// 변경된 스타일 적용
		ProgressBar->SetWidgetStyle(Style);
	}
}