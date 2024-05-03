// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
//#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
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
	virtual void SetEnemyData(const FEnemyDataTableRow* InData);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
protected:
	virtual void OnConstrution(const FTransform& Transform);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* CapsuleComponent;

	//UPROPERTY(EditAnywhere, Category = Collision)
	//UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditAnywhere)
	UFloatingPawnMovement* Movement;

protected:
	const FEnemyDataTableRow* EnemyDataTableRow = nullptr;

};