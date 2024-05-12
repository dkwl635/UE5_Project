// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Slot/SkillSlot.h"
#include "Actors/PlayerCharacter/PlayerCharacter.h"
#include "Components/SkillComponent.h"
#include "Actors/Skill/SkillBase.h"
#include "Styling/SlateBrush.h"

void USkillSlot::SetImage(UTexture2D* InTexture)
{
	if (Sk_Icon && InTexture)
	{
		Sk_Icon->SetBrushFromTexture(InTexture);
		Sk_Icon->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
	}
}