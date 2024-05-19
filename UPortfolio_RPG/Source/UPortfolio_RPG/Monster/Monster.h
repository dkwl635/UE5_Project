// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Pawn.h"
#include "Monster.generated.h"

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

	// FireScream event
	UFUNCTION(BlueprintCallable, Category = "Monster")
	void FireScream();

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

	// Particle system
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* FireScreamEffect;

	// Animation montage
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* FireScreamMontage;

	// Scream boolean
	bool bIsScream;

	// Timeline for movement
	FTimeline ScreamTimeline;

	// Timeline's float curve
	UPROPERTY()
	UCurveFloat* ScreamCurve;

	// Timeline callback
	UFUNCTION()
	void HandleScreamProgress(float Value);

	// Function to handle the end of the montage
	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	// Delay timer handle
	FTimerHandle DelayTimerHandle;

private:
	void ScreamDelay();
};
