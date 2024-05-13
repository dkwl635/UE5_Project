// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

struct FInputActionValue;
class UStatusComponent;
class USkillComponent;
struct FSkillDataTableRow;
struct FStatusDataTableRow;

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
	void OnSkill_Q(const FVector& HitPoint);
	void OnSkill_W(const FVector& HitPoint);
	void OnSpace(const FVector& HitPoint);
	void OnDefaultAttack(const FVector& HitPoint);

public:
	void DefaultAttackCheck();

public:
	UStatusComponent* GetStatusComponent() { return StatusComponent; }
	USkillComponent* GetSkillComponent() { return SkillComponent; }
	FTimerHandle& GetTimerHandle() { return SpaceCoolTimer; }
	float GetSpaceCoolTime() { return SpaceCoolTime; }

protected:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComponent;
	UPROPERTY(EditAnywhere, Category = "Status")
	UStatusComponent* StatusComponent;
	UPROPERTY(EditAnywhere, Category = "Skill")
	USkillComponent* SkillComponent;

protected:
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/UPortfolio_RPG.CharacterAnimDataTableRow"))
	FDataTableRowHandle AnimDataTableRowHandle;
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/UPortfolio_RPG.SkillDataTableRow"))
	FDataTableRowHandle SkillDataTableRowHandle;
	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/UPortfolio_RPG.StatusDataTableRow"))
	FDataTableRowHandle StatusDataTableRowHandle;

public:
	UPROPERTY()
	UAnimMontage* AttackMontage_A;
	UPROPERTY()
	UAnimMontage* AttackMontage_B;
	UPROPERTY()
	UAnimMontage* AttackMontage_C;
	UPROPERTY()
	UAnimMontage* SpaceMontage;

	UAnimMontage* CurrentMontage;

protected:
	FTimerHandle SpaceCoolTimer;
	FTimerHandle SpaceTimer;

	UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Space")
	float SpaceCoolTime = 5.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Space")
	float RemainingTime = 0.f;

public:
	UPROPERTY(BlueprintReadOnly)
	bool bIsSpace = false;
	bool bIsDown = false;
	bool bOnAttack = false;

protected:
	class UPlayerAnimInstance* PlayerAnim = nullptr;
	const FCharacterAnimDataTableRow* AnimDataTableRow = nullptr;
	const FSkillDataTableRow* SkillDataTableRow = nullptr;
	const FStatusDataTableRow* StatusDataTableRow = nullptr;
private:
	void LookAtMouseCursor(const FVector& HitPoint);
};
