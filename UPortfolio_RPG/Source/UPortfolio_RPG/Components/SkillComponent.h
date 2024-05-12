// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkillComponent.generated.h"

class ASkillBase;
class APlayerCharacter;

USTRUCT()
struct UPORTFOLIO_RPG_API FSkillDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ASkillBase>> Skills;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UPORTFOLIO_RPG_API USkillComponent : public UActorComponent
{
	GENERATED_BODY()

	friend APlayerCharacter;

public:	
	// Sets default values for this component's properties
	USkillComponent();
	void SetSkillData(const FSkillDataTableRow* InData);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	TSubclassOf<ASkillBase> GetSkill(int32 InIndex) { return Skills[InIndex]; }

protected:
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<ASkillBase>> Skills;

	const FSkillDataTableRow* SkillDataTableRow = nullptr;
};
