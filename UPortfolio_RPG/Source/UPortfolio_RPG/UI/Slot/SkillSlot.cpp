// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Slot/SkillSlot.h"
#include "Actors/PlayerCharacter/PlayerCharacter.h"
#include "Components/SkillComponent.h"
#include "Actors/Skill/SkillBase.h"
#include "Actors/PlayerCharacter/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void USkillSlot::SetImage(UTexture2D* InTexture)
{
	if (Sk_Icon && InTexture)
	{
		Sk_Icon->SetBrushFromTexture(InTexture);
		Sk_Icon->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
	}
}

void USkillSlot::SetProgressBar()
{
	Super::SetProgressBar();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PlayerController) return;

	APlayerCharacter* Player = Cast<APlayerCharacter>(PlayerController->GetCharacter());
	if (!Player) return;

	RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(CoolTimer);
}