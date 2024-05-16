// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/RPGUserWidget.h"
#include "ItemInfoUserWdiget.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API UItemInfoUserWdiget : public URPGUserWidget
{
	GENERATED_BODY()


public:

	UPROPERTY(meta = (BindWdiget))
	class UCanvasPanel* CanvasPanel;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* ImgIcon;

	UPROPERTY(meta = (BindWdiget))
	class UTextBlock* ItmeNameTextBlock;

	UPROPERTY(meta = (BindWdiget))
	class UTextBlock* ItemInfoTextBlock;

public:
	void ShowItemInfo(struct ShowBoxData Data);

};
