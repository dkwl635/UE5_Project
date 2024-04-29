// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasicPlayerController.generated.h"

class UNiagaraSystem;

UCLASS()
class UPORTFOLIO_RPG_API ABasicPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ABasicPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

protected:
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased(); 
	void OnDefaultAttack();
	void OnSkill();

private:
	FVector CachedDestination;
};
