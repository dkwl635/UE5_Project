// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SkillBase.generated.h"

UCLASS()
class UPORTFOLIO_RPG_API USkillBase : public UObject
{
	GENERATED_BODY()
	
protected:
	virtual void UseSkill() {}

public:
	UPROPERTY(EditAnywhere)
	FName Sk_Name;
	UPROPERTY(EditAnywhere)
	FText Sk_Desc;
	UPROPERTY(EditAnywhere)
	float Sk_CoolTime;
	UPROPERTY(EditAnywhere)
	float Sk_Damage;
	UPROPERTY(EditAnywhere)
	float Sk_ManaUsage;
	UPROPERTY(EditAnywhere)
	UTexture2D* Sk_Image;
	
};
