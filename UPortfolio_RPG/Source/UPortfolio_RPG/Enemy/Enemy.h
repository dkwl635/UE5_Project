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

/*USTRUCT()
struct UPORTFOLIO_RPG_API FEnemyDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "Enemy")
	float CapsuleRadius;              //캡슐 컴포넌트 반지름

	UPROPERTY(EditAnywhere, Category = "Enemy")
	float CapsuleHalfHeight;          //캡슐 컴포넌트 반높이

	UPROPERTY(EditAnywhere, Category = "Enemy")
	USkeletalMesh* SkeletalMesh;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	FTransform SkeletalMeshTransform;   //enemy 상대적 위치

	UPROPERTY(EditAnywhere, Category = "Enemy")
	float EnemyHP;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	TSubclassOf<UAnimInstance> AnimClass;   //애니메이션

	UPROPERTY(EditAnywhere, Category = "Enemy")
	UParticleSystem* ParticleAttackSystem;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	UParticleSystemComponent* ParticleAttackSystemComponent;

	UPROPERTY(EditAnywhere, Category = "Enemy")
	FTransform ParticleTransform;
};*/

UCLASS()
class UPORTFOLIO_RPG_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();
	~AEnemy();
//	virtual void SetEnemyData(const FDataTableRowHandle& InDataTableRowHandle);
	//virtual void SetEnemyData(const FEnemyData* InData);
//	virtual void SetEnemyData(const FEnemyDataTableRow* InData);
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

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HPBarWidget;

	UPROPERTY(VisibleAnywhere)
	UParticleSystem* ParticleAttackSystem;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* ParticleAttackSystemComponent;

	UPROPERTY(EditAnywhere)
	UEnemyAnimInstance* EnemyAnim;

	UPROPERTY()
	UStatusComponent* EnemyState;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* StatusWidget;

	UPROPERTY()
	UStatusbarUserWidget* EnemyStatusUserWidget;

	UPROPERTY()
	float MaxHP;

//	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/UPortfolio_RPG.EnemyDataTableRow"))
//	FDataTableRowHandle DataTableRowHandle;

protected:
//	const FEnemyDataTableRow* EnemyDataTableRow = nullptr;


public:										 
	UPROPERTY(EditAnywhere)             //animInstance에서 가져다 쓰기위해서..
	UFloatingPawnMovement* Movement;

// attack and damage
public:
	void Attack();
	void AttackCheck();
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;


	// montage
	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	// particle
	void PlayAttackParticle();

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsAttacking; 


public:
	//void SetEnemy(const FName& InKey);
	UDataSubsystem* DataSubsystem;


	bool Init();
	void SetEnemyDataSubsystem(const FName& InKey);
	bool AddEnemy(const FName& InKey);

};