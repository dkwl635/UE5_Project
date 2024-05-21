// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Animation/WidgetAnimation.h"
#include "PrintDamageUserWidget.generated.h"

UCLASS()
class UPORTFOLIO_RPG_API UPrintDamageUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	void SetDamage(float InDamage);
	void SetOwner(AActor* Owner);
	UFUNCTION()
	void OnAnimFinished();

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DamageText;
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FloatingText;

	AActor* OwningActor = nullptr;
};
