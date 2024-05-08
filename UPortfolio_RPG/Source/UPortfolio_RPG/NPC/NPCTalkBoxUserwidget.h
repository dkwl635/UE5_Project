// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/RPGUserWidget.h"
#include "NPCTalkBoxUserwidget.generated.h"

/**
 * 
 */
UCLASS()
class UPORTFOLIO_RPG_API UNPCTalkBoxUserwidget : public URPGUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TWeakObjectPtr<class ANPCManager> NPCManager;
public:

	class UTextBlock;
	class UButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UWidgetSwitcher* TextBoxSwitcher;
	UPROPERTY(EditAnywhere, BlueprintReadWrite , meta = (BindWidget))
	UTextBlock* NameTextBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* ContentTextBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* TalkButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* ShopButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* QuestButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* CloseButton;
	

public :

	void OpenUI();
};
