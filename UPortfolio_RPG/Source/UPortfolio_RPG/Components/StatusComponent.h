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
	float MaxHP;
	UPROPERTY(EditAnywhere)
	float MaxMP;
	UPROPERTY(EditAnywhere)
	float AttackDamage;
	UPROPERTY(EditAnywhere)
	float Speed;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPORTFOLIO_RPG_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	void SetStatusData(const FStatusDataTableRow* InData);

public:
	inline float GetMaxHP() { return MaxHP; }
	inline float GetCurrentHP() { return CurrentHP; }
	inline void SetMaxHP(float InHP)
	{
		if (MaxHP <= 0) { MaxHP = 0; }
		else { MaxHP = InHP; }
	}
	inline void SetCurrentHP(float InHP)
	{
		if (CurrentHP <= 0) { CurrentHP = 0; }
		else { CurrentHP = InHP; }
	}
	inline float GetMaxMP() { return MaxMP; }
	inline float GetCurrentMP() { return CurrentMP; }
	inline void SetMaxMP(float InMP) { MaxMP = InMP; }
	inline void SetCurrentMP(float InMP)
	{
		if (CurrentMP <= 0) { CurrentMP = 0; }
		else { CurrentMP = InMP; }
	}
	inline float GetAttackDamage() { return AttackDamage; }
	inline float GetMinAttackDamage() { return MinAttackDamage; }
	inline float GetMaxAttackDamage() { return MaxAttackDamage; }
	inline void SetAttackDamage(float Damage) { AttackDamage = Damage; }
	inline float GetSpeed() { return Speed; }
	inline void SetSpeed(float InSpeed) { Speed = InSpeed; }
	inline void SetSuperArmor(bool InSuperArmor) { bSuperArmor = InSuperArmor; }
	inline void SetSuperStance(bool InSuperStance) { bSuperStance = InSuperStance; }

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
