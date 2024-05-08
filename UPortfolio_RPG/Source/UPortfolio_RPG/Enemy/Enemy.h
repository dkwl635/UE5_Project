// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "Components/StatusComponent.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Enemy/UI/StatusbarUserWidget.h"
#include "Enemy.generated.h"

USTRUCT()
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

};

UCLASS()
class UPORTFOLIO_RPG_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();
	~AEnemy();
	virtual void SetEnemyData(const FDataTableRowHandle& InDataTableRowHandle);
	virtual void SetEnemyData(const FEnemyDataTableRow* InData);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
protected:
	virtual void OnConstruction(const FTransform& Transform) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

private:
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CapsuleComponent;

	//UPROPERTY(EditAnywhere, Category = Collision)
	//UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = UI)
	class UWidgetComponent* HPBarWidget;

	UPROPERTY(EditAnywhere, meta = (RowType = "/Script/UPortfolio_RPG.EnemyDataTableRow"))
	FDataTableRowHandle DataTableRowHandle;

	


public:										 
	UPROPERTY(EditAnywhere)             //animInstance에서 가져다 쓰기위해서..
	UFloatingPawnMovement* Movement;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	

protected:
	const FEnemyDataTableRow* EnemyDataTableRow = nullptr;

public:
	void Attack();
	void AttackCheck();

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool IsAttacking;

	UPROPERTY()
	class UEnemyAnimInstance* EnemyAnim;


	UPROPERTY()
	UStatusComponent* EnemyState;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* StatusWidget;

	UPROPERTY()
	UStatusbarUserWidget* EnemyStatusUserWidget;

	UPROPERTY()
	float MaxHP;

};