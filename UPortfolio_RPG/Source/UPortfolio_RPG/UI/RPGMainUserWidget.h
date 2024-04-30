// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPGUserWidget.h"
#include "Components/Button.h"
#include "RPGMainUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API URPGMainUserWidget : public URPGUserWidget
{
	GENERATED_BODY()
	UPROPERTY(meta = (BindWidget))
	UButton* InventoryBtn;

	
private :

	UFUNCTION(BlueprintCallable)
	void OpenInventoryUI();

public :
	//인벤토리 UI
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<URPGUserWidget> InventoryUI;
	

};
