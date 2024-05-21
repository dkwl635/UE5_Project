// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PrintDamageTextActor.generated.h"

class UWidgetComponent;

UCLASS()
class UPORTFOLIO_RPG_API APrintDamageTextActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APrintDamageTextActor();

	void SetWidgetText(APawn* Damaged, float InDamage, FVector InLocation);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*FTimerHandle Timer;

	UFUNCTION()
	void DestroyActor();*/
protected:
	UPROPERTY()
	UWidgetComponent* Widget;
};
