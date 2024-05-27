// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"

USTRUCT()
struct UPORTFOLIO_RPG_API FStatusDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float MaxHP = 0;
	UPROPERTY(EditAnywhere)
	float MaxMP = 0;
	UPROPERTY(EditAnywhere)
	float AttackDamage = 0;
	UPROPERTY(EditAnywhere)
	float Speed = 0;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPORTFOLIO_RPG_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusComponent();

protected:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, 
		FActorComponentTickFunction* ThisTickFunction) override;
	
public:	
	void SetStatusData(const FStatusDataTableRow* InData);

public:
	float GetMaxHP() { return MaxHP; }
	float GetCurrentHP() { return CurrentHP; }
	void SetMaxHP(float InHP){ MaxHP = InHP; }
	void SetCurrentHP(float InHP) { CurrentHP = InHP; }
	void AddToCurrentHP(float InHP)
	{
		CurrentHP += InHP;
		if (MaxHP <= CurrentHP)
			CurrentHP = MaxHP;
	}
	void DamageToCurrentHP(float InHP)
	{
		CurrentHP -= InHP;
		if (CurrentHP <= 0.f)
			CurrentHP = 0.f;
	}
	
	float GetMaxMP() { return MaxMP; }
	float GetCurrentMP() { return CurrentMP; }
	void SetMaxMP(float InMP) { MaxMP = InMP; }
	void AddToCurrentMP(float InMP)
	{
		CurrentMP += InMP;
		if (MaxMP <= CurrentMP)
			CurrentMP = MaxMP;
	}
	void UseCurrentMP(float InMP)
	{
		CurrentMP -= InMP;
		if (CurrentMP <= 0.f)
			CurrentMP = 0.f;
	}

	float GetAttackDamage() { return AttackDamage; }
	void SetAttackDamage(float Damage) { AttackDamage = Damage; }
	float GetRandDamage() { return FMath::RandRange(MinAttackDamage, MaxAttackDamage); }

	float GetSpeed() { return Speed; }
	void SetSpeed(float InSpeed) { Speed = InSpeed; }

	void SetSuperArmor(bool InSuperArmor) { bSuperArmor = InSuperArmor; }
	void SetSuperStance(bool InSuperStance) { bSuperStance = InSuperStance; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxHP;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CurrentHP;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxMP;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float CurrentMP;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AttackDamage;
	float MinAttackDamage;
	float MaxAttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Speed;
		
	bool bSuperArmor;
	bool bSuperStance;

};
