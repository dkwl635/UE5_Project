// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

struct FInputActionValue;
class UStatusComponent;
class USkillComponent;

UCLASS()
class UPORTFOLIO_RPG_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void OnSkill(const FInputActionValue& InputActionValue);
	void OnSpace(const FVector& HitPoint);
	void OnDefaultAttack(const FVector& HitPoint);

protected:
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArmComponent;
	UPROPERTY(EditAnywhere)
	class UCameraComponent* CameraComponent;
	UPROPERTY(EditAnywhere)
	UStatusComponent* StatusComponent;
	UPROPERTY(EditAnywhere, Category = "Skill")
	USkillComponent* SkillComponent;

protected:
	UPROPERTY(EditAnywhere)
	UAnimMontage* AttackMontage;

protected:
	FTimerHandle SpaceCoolTimer;
	FTimerHandle SpaceTimer;

	UPROPERTY(EditAnywhere)
	float SpaceCoolTime = 5.f;
	UPROPERTY(EditAnywhere)
	float SpaceDistance = 10000.f;

public:
	UPROPERTY(VisibleAnywhere, Category = "Space")
	bool bIsSpace = false;
};
