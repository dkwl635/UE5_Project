// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "Components/StatusComponent.h"
#include "Enemy/UI/StatusbarUserWidget.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Actors/PlayerCharacter/PlayerCharacter.h"
#include "DataSubsystem/DataSubsystem.h"
#include "Animation/EnemyAnimInstance.h"
#include "Enemy.generated.h"

class UEnemyPool;
class UWidgetComponent;



UCLASS()
class UPORTFOLIO_RPG_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();
	~AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
protected:
	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

// Datatable variable
private:
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CapsuleComponent;
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* SkeletalMeshComponent;
	UPROPERTY()
	UParticleSystem* ParticleAttackSystem;
	UPROPERTY()
	UParticleSystemComponent* ParticleAttackSystemComponent;
	UPROPERTY(EditAnywhere)
	UEnemyAnimInstance* EnemyAnim;
	UPROPERTY(EditAnywhere)
	UStatusComponent* EnemyState;
	UPROPERTY(EditAnywhere)
	UWidgetComponent* StatusWidget;
	UPROPERTY()
	UStatusbarUserWidget* EnemyStatusUserWidget;

public:										 
	UPROPERTY(EditAnywhere)             //animInstance에서 가져다 쓰기위해서..
	UFloatingPawnMovement* Movement;

// attack and damage
public:
	void Attack();
	void AttackCheck();
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	//// montage
	//UFUNCTION()
	//void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	// particle
	void PlayAttackParticle();

public:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	bool IsAttacking; 
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	bool IsDead;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	bool IsSpawn;
	int32 PurificationScore = 0;

	UEnemyAnimInstance* GetAnimInstance() { return EnemyAnim; }
	UStatusComponent* GetStatusComponent() { return EnemyState; }

public:
	UDataSubsystem* DataSubsystem;

	bool Init();
	bool AddEnemy(const FName& InKey);
	void SetPool(UEnemyPool* InPool) { Pool = InPool; }
	void Reset();

	UPROPERTY(EditAnywhere, Category = "Enemy")
	FName SpawnEnemyName = "Lane"; // Lane 이름의 접두사를 설정하기 위한 변수

	UPROPERTY()
	TArray<FName> EnemyTypes = { TEXT("Lane"), TEXT("Prime"), TEXT("Green"), TEXT("Black") };

	UEnemyPool* Pool = nullptr;
};