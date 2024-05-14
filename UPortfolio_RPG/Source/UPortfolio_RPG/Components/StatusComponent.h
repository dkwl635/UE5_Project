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
	float GetMaxHP() { return MaxHP; }
	float GetCurrentHP() { return CurrentHP; }
	void SetMaxHP(float InHP) { MaxHP = InHP; }
	void SetCurrentHP(float InHP) { CurrentHP = InHP; }
	float GetMaxMP() { return MaxMP; }
	float GetCurrentMP() { return CurrentMP; }
	void SetMaxMP(float InMP) { MaxMP = InMP; }
	void SetCurrentMP(float InMP) { CurrentMP = InMP; }
	float GetAttackDamage() { return AttackDamage; }
	void SetAttackDamage(float Damage) { AttackDamage = Damage; }
	void SetSuperArmor(bool InSuperArmor) { bSuperArmor = InSuperArmor; }
	void SetSuperStance(bool InSuperStance) { bSuperStance = InSuperStance; }

protected:
	UPROPERTY(EditAnywhere)
	float MaxHP;
	UPROPERTY(EditAnywhere)
	float CurrentHP;
	UPROPERTY(EditAnywhere)
	float MaxMP;
	UPROPERTY(EditAnywhere)
	float CurrentMP;
	UPROPERTY(EditAnywhere)
	float AttackDamage;
		
	bool bSuperArmor;
	bool bSuperStance;

};
