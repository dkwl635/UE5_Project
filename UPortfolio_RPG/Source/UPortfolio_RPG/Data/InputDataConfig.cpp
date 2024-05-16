// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/InputDataConfig.h"

UInputDataConfig::UInputDataConfig()
{
	{
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> Asset
		{ TEXT("/Script/EnhancedInput.InputMappingContext'/Game/KSH/Character/Input/IMC_Player.IMC_Player'") };
		check(Asset.Succeeded());
		InputMappingContext = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/KSH/Character/Input/IA_Move.IA_Move'") };
		check(Asset.Succeeded());
		Move = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/KSH/Character/Input/IA_DefaultAttack.IA_DefaultAttack'") };
		check(Asset.Succeeded());
		DefaultAttack = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/KSH/Character/Input/IA_Skill_Q.IA_Skill_Q'") };
		check(Asset.Succeeded());
		Skill_Q = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/KSH/Character/Input/IA_Skill_W.IA_Skill_W'") };
		check(Asset.Succeeded());
		Skill_W = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/KSH/Character/Input/IA_Space.IA_Space'") };
		check(Asset.Succeeded());
		Space = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/KSH/Character/Input/IA_OpenSkillUI.IA_OpenSkillUI'") };
		check(Asset.Succeeded());
		OpenSkillUI = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/KSH/Character/Input/IA_ZoomWheel.IA_ZoomWheel'") };
		check(Asset.Succeeded());
		ZoomWheel = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/KSH/Character/Input/IA_AddHP.IA_AddHP'") };
		check(Asset.Succeeded());
		AddHP = Asset.Object;
	}
}
