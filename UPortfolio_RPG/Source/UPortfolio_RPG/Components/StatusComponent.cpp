// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StatusComponent.h"

// Sets default values for this component's properties
UStatusComponent::UStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	MinAttackDamage = AttackDamage * 0.9;
	MaxAttackDamage = AttackDamage * 1.1;
}

void UStatusComponent::SetStatusData(const FStatusDataTableRow* InData)
{
	ensure(InData);
	if (!InData) { return; }

	MaxHP = InData->MaxHP;
	CurrentHP = MaxHP;
	MaxMP = InData->MaxMP;
	CurrentMP = MaxMP;
	AttackDamage = InData->AttackDamage;
	Speed = InData->Speed;
}