// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ChaosDungeonInputDataConfig.h"

UChaosDungeonInputDataConfig::UChaosDungeonInputDataConfig()
{
	{
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> Asset
		{ TEXT("/Script/EnhancedInput.InputMappingContext'/Game/KSH/ChaosDunGeon/Input/IMC_ChaosDungeon.IMC_ChaosDungeon'") };
		check(Asset.Succeeded());
		InputMappingContext = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/KSH/ChaosDunGeon/Input/IA_Start.IA_Start'") };
		check(Asset.Succeeded());
		StartMove = Asset.Object;
	}
}
