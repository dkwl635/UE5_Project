// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasicPlayerController.generated.h"

struct FInputActionValue;

UCLASS()
class UPORTFOLIO_RPG_API ABasicPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ABasicPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

protected:
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased(); 
	void OnDefaultAttack(const FInputActionValue& InputActionValue);

private:
	float FollowTime;
	FVector CachedDestination;
};
