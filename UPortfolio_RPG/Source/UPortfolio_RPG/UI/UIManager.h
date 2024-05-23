// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UI/UIEnum.h"
#include "UIManager.generated.h"



UCLASS()
class UPORTFOLIO_RPG_API AUIManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUIManager();

	static TWeakObjectPtr<AUIManager> UIManager;

protected:
	virtual void BeginPlay() override;
	

public :
	TSubclassOf<UUserWidget> MainUIBP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class URPGMainUserWidget* PlayerUI;
	TWeakObjectPtr<class UCanvasPanelSlot> TopPopupUI;

public  :
	bool isShopOpen;
	UPROPERTY()
	TArray<ERPG_UI> UIList;

public:
	UFUNCTION(BlueprintCallable)
	void ShowUI(ERPG_UI Type);
	UFUNCTION(BlueprintCallable)
	void HideUI(ERPG_UI Type);
	UFUNCTION(BlueprintCallable)
	void TopHideUI();
	UFUNCTION(BlueprintCallable)
	class URPGUserWidget* GetRPGUI(ERPG_UI UIType);
	UFUNCTION(BlueprintCallable)
	bool IsShowUI(ERPG_UI UIType);
	UFUNCTION(BlueprintCallable)
	void GetRPGUIToggle(ERPG_UI UIType);
public:
	class UCanvasPanelSlot* GetCanvasPanel(ERPG_UI Type);
	void PlayerGoodsUIRefresh();
	void ShowItemBox(FVector2D SpawnPos , struct  ShowBoxData Data);
	void HideItemBox();
	void RefreshUI(ERPG_UI UIType);
	void SetSkillUI();
	void SetYesNoButton(FOnButtonCallBack YesButtonFunc, FOnButtonCallBack NoButtonFunc, FText BoxText);
	
};
