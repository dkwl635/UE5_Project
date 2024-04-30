// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillBase.generated.h"

UCLASS()
class UPORTFOLIO_RPG_API USkillBase : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	FName SkillName;
	UPROPERTY(EditAnywhere)
	float CoolTime;
	UPROPERTY(EditAnywhere)
	float Damage;
	UPROPERTY(EditAnywhere)
	float ManaUsage;
	UPROPERTY(EditAnywhere)
	UTexture2D* SkillImage;
	UPROPERTY(EditAnywhere)
	FText SkillDesc;
};
