// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SkillComponent.h"
#include "Actors/Skill/SkillBase.h"

// Sets default values for this component's properties
USkillComponent::USkillComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void USkillComponent::SetSkillData(const FSkillDataTableRow* InData)
{
	ensure(InData);
	if (!InData) { return; }

	for (auto* Skill : Skills)
	{
		if (Skill)
			Skill->ConditionalBeginDestroy();
	}
	Skills.Empty();

    for (TSubclassOf<ASkillBase> SkillClass : InData->Skills)
    {
        if (*SkillClass != nullptr)
        {
            ASkillBase* NewSkill = NewObject<ASkillBase>(GetOwner(), SkillClass);
            if (NewSkill != nullptr)
            {
                Skills.Add(NewSkill);
            }
        }
    }
}

// Called when the game starts
void USkillComponent::BeginPlay()
{
	Super::BeginPlay();

}