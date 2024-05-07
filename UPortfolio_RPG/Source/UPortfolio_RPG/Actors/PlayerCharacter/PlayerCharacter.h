// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

struct FInputActionValue;
class UStatusComponent;
class USkillComponent;

USTRUCT()
struct UPORTFOLIO_RPG_API FCharacterAnimDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackMontage_A;
	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackMontage_B;
	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackMontage_C;
	UPROPERTY(EditAnywhere, Category = "Evade")
	UAnimMontage* SpaceMontage;
	UPROPERTY(EditAnywhere, Category = "Skill")
	UAnimMontage* Skill_Q_Montage;

};

UCLASS()
class UPORTFOLIO_RPG_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	void SetAnimData(const FDataTableRowHandle& InDataTableRowHandle);
	void SetAnimData(const FCharacterAnimDataTableRow* InData);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void OnSkill(const FVector& HitPoint);
	void OnSpace(const FVector& HitPoint);
	void OnDefaultAttack(const FVector& HitPoint);

public:
	void DefaultAttackCheck();

public:
	UStatusComponent* GetStatusComponent() { return StatusComponent; }

protected:
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArmComponent;
	UPROPERTY(EditAnywhere)
	class UCameraComponent* CameraComponent;
	UPROPERTY(EditAnywhere, Category = "Status")
	UStatusComponent* StatusComponent;
	UPROPERTY(EditAnywhere, Category = "Skill")
	USkillComponent* SkillComponent;
	/*UPROPERTY(EditAnywhere)
	UCapsuleComponent* SwordCollider;*/

protected:
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/UPortfolio_RPG.CharacterAnimDataTableRow"))
	FDataTableRowHandle DataTableRowHandle;

public:
	UPROPERTY(EditAnywhere, Category = "Montage")
	UAnimMontage* AttackMontage_A;
	UPROPERTY(EditAnywhere, Category = "Montage")
	UAnimMontage* AttackMontage_B;
	UPROPERTY(EditAnywhere, Category = "Montage")
	UAnimMontage* AttackMontage_C;
	UPROPERTY(EditAnywhere, Category = "Montage")
	UAnimMontage* SpaceMontage;
	UPROPERTY(EditAnywhere, Category = "Skill")
	UAnimMontage* Skill_Q_Montage;

	UAnimMontage* CurrentMontage;

protected:
	FTimerHandle SpaceCoolTimer;
	FTimerHandle SpaceTimer;

	UPROPERTY(EditAnywhere)
	float SpaceCoolTime = 2.f;

public:
	UPROPERTY(VisibleAnywhere, Category = "Space")
	bool bIsSpace = false;
	
	bool bOnAttack = false;

protected:
	const FCharacterAnimDataTableRow* AnimDataTableRow = nullptr;

private:
	void LookAtMouseCursor(const FVector& HitPoint);
};
