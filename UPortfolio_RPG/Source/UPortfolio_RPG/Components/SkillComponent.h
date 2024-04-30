// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillComponent.generated.h"

class USkillBase;

USTRUCT()
struct UPORTFOLIO_RPG_API FSkillDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FName SkillName;
	UPROPERTY(EditAnywhere)
	float CoolTime;
	UPROPERTY(EditAnywhere)
	float Damage;
	UPROPERTY(EditAnywhere)
	float ManaUsage;
	UPROPERTY(EditAnywhere)
	UTexture2D* SkillImage;
	UPROPERTY(EditAnywhere)
	FText SkillDesc;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPORTFOLIO_RPG_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	TArray<TSubclassOf<USkillBase>> Skills;
};
