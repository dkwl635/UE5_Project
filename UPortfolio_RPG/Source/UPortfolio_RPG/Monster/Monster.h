// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Pawn.h"
#include "Monster/Animation/MonsterAnimInstance.h"
#include "Monster.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnTimelineFinished);

UCLASS()
class UPORTFOLIO_RPG_API AMonster : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Root component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCapsuleComponent* CapsuleComponent;

	// Box collision component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollision;

	// Skeletal mesh component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditAnywhere)
	UMonsterAnimInstance* MonsterAnim;


public: //공격 패턴 함수
	// FireScream Event
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void FireScream();

	// AttackRange Event 
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void AttackRange();


//FireScream 이용 변수
private: 
	// Particle system
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* FireScreamEffect;

	// Animation montage
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* FireScreamMontage;

	// Timeline for movement
	FTimeline ScreamTimeline;
	int TimeLineCnt = 0;

	// Timeline's float curve
	UPROPERTY()
	UCurveFloat* ScreamCurve;

	// Timeline callback
	UFUNCTION()
	void HandleScreamProgress(float Value);

	// Function to handle the end of the montage
	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	// BoxCollision의 오버랩 이벤트 핸들러
	UFUNCTION()
	void OnBoxCollisionOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//FireScream 공격 끝
	UFUNCTION()
	void FinishFire();


//AttackRange 이용 변수
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Attack")
	FVector AttackRangeLocation = FVector(0.f,0.f,0.f);

	UPROPERTY()
	class AAttackRangeActor* AttackRangeActor;











//Delay 관리
private: 
	// Delay timer handle
	FTimerHandle DelayTimerHandle;
	void ScreamDelay();


public:  //Animation Bool
	// Scream boolean
	bool IsScream = true;
	
};
