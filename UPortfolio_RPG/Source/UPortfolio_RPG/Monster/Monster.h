// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "Monster/Animation/MonsterAnimInstance.h"
#include "NiagaraFunctionLibrary.h"
#include "Enemy/UI/StatusbarUserWidget.h"
#include "Monster.generated.h"

class UWidgetComponent;

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
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	//공격 데미지 변수
public:
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void MonsterAttackDamage(AActor* OtherActor, float Damage);

	float FireAttackDamage = 100;
	float RayAttackDamage = 100;
	float RangeAttackDamage = 50;
	float HitAttackDamage = 200;

private:


private:
	void DisplayDamage(float InDamage);

public:
	float MaxHP = 4000;
	float CurrentHP = 0;

public:
	UPROPERTY(EditAnywhere)             //animInstance에서 가져다 쓰기위해서..
		UFloatingPawnMovement* Movement;


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

	UPROPERTY(Transient)
	UMonsterAnimInstance* MonsterAnim;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI_Visiable", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* StatusWidget;
	UPROPERTY()
	UStatusbarUserWidget* MonsterStatusUserWidget;

public: //공격 패턴 함수
	// FireScream Event
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void FireScream();

	// AttackRange Event 
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void AttackRange();

	UFUNCTION(BlueprintCallable, Category = "Attack")
	void MonsterHitAttackTrace(FName SocketName, FVector Location);

//FireScream 이용 변수
private: 
	// Particle system
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* FireScreamEffect;

	UParticleSystemComponent* SpawnedEffect;

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

	int RangeCnt = 1;


//AttackRange 이용 변수
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Attack")
	FVector AttackRangeLocation = FVector(0.f,0.f,0.f);

	UPROPERTY()
	class AAttackRangeActor* AttackRangeActor;

	// Particle system
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UNiagaraSystem* AttackRangeEffect;





//공격 끝을 알리는 변수
	private:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Finish, Meta = (AllowPrivateAccess = true))
		bool IsAttackFinish = false;





//Delay 관리
private: 
	// Delay timer handle
	FTimerHandle DelayTimerHandle;
	void ScreamDelay();
	void RangeSpawnDelay();
	void DestroyRangeActor();
	


public:  //Animation Bool
	// Scream boolean
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = MonsterAnim, Meta = (AllowPrivateAccess = true))
	bool IsScream = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterAnim, Meta = (AllowPrivateAccess = true))
	bool IsDetach = false;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = MonsterAnim, Meta = (AllowPrivateAccess = true))
	bool IsRange = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterAnim, Meta = (AllowPrivateAccess = true))
	bool IsMove = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterAnim, Meta = (AllowPrivateAccess = true))
	bool IsDead = false;
	
};
