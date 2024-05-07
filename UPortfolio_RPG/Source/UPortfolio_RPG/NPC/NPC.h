// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPC.generated.h"

UCLASS()
class UPORTFOLIO_RPG_API ANPC : public AActor
{
	GENERATED_BODY()
	
public:
	class ANPCManager* NPCManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* BodyCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* Body;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* TriggerCollision;

public:	
	// Sets default values for this actor's properties
	ANPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
