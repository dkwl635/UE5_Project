// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Skill/SkillInterfaceUserWidget.h"
#include "Actors/PlayerCharacter/PlayerCharacter.h"



void USkillInterfaceUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UI_SkillSlot_0->GetKeyPadTextBlock()->SetText(FText::FromString(TEXT("Q")));
	UI_SkillSlot_1->GetKeyPadTextBlock()->SetText(FText::FromString(TEXT("W")));
	UI_SkillSlot_2->GetKeyPadTextBlock()->SetText(FText::FromString(TEXT("E")));
	UI_SkillSlot_3->GetKeyPadTextBlock()->SetText(FText::FromString(TEXT("R")));
	UI_SkillSlot_4->GetKeyPadTextBlock()->SetText(FText::FromString(TEXT("A")));
	UI_SkillSlot_5->GetKeyPadTextBlock()->SetText(FText::FromString(TEXT("S")));
	UI_SkillSlot_6->GetKeyPadTextBlock()->SetText(FText::FromString(TEXT("D")));
	UI_SkillSlot_7->GetKeyPadTextBlock()->SetText(FText::FromString(TEXT("F")));
}

void USkillInterfaceUserWidget::Init()
{
	UI_SkillSlot_0->SetCachedSkill(0);
	UI_SkillSlot_1->SetCachedSkill(1);
	UI_SkillSlot_2->SetCachedSkill(2);
	UI_SkillSlot_3->SetCachedSkill(3);
	UI_SkillSlot_4->SetCachedSkill(4);
	UI_SkillSlot_5->SetCachedSkill(5);
	UI_SkillSlot_6->SetCachedSkill(6);
	UI_SkillSlot_7->SetCachedSkill(7);
}
