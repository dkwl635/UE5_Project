// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPGUserWidget.generated.h"

/**
 * 
 */	
//DECLARE_DYNAMIC_DELEGATE_OneParam(FDele_Dynamic_OneParam, UCanvasPanelSlot*, UI);
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDele_Dynamic_OneParam, UCanvasPanelSlot*, MoveUI);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDele_Dynamic_OneParam, UCanvasPanel*, SomeParameter);

UCLASS(BlueprintType)
class UPORTFOLIO_RPG_API URPGUserWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	
public:
	UFUNCTION(BlueprintCallable)
	virtual void RefreshUI();
	UFUNCTION(BlueprintCallable)
	virtual void Init();
	
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FDele_Dynamic_OneParam StartUIMove;

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FDele_Dynamic_OneParam EndUIMove;


};
