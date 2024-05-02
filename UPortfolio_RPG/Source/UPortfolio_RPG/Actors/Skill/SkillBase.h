// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillBase.generated.h"

UCLASS()
class UPORTFOLIO_RPG_API ASkillBase : public AActor
{
	GENERATED_BODY()
	
protected:
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser);

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
