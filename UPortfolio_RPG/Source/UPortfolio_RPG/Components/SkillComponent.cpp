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

	const int32 Num = InData->Skills.Num();
	Skills.Reserve(Num);
	for(int32 i=0;i<Num;++i)
		Skills.Add(InData->Skills[i]);
}

// Called when the game starts
void USkillComponent::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void USkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}