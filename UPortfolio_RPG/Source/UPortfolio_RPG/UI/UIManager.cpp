// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIManager.h"
#include "UI/RPGMainUserWidget.h"
#include "UI/RPGUserWidget.h"
#include "Item/ItemData.h"
#include "Components/CanvasPanelSlot.h"


TWeakObjectPtr<AUIManager> AUIManager::UIManager = nullptr;
// Sets default values
AUIManager::AUIManager()
{
	PrimaryActorTick.bCanEverTick = false;
	static ConstructorHelpers::FClassFinder<URPGMainUserWidget> FindUI(TEXT("Script/UMGEditor.WidgetBlueprint'/Game/KJW/UI/BPUI_MainUI.BPUI_MainUI_C'"));
 	MainUIBP = FindUI.Class;

}

// Called when the game starts or when spawned
void AUIManager::BeginPlay()
{
	Super::BeginPlay();
	
	UIManager = this;

	if (MainUIBP)
	{
		auto Widget = CreateWidget<UUserWidget>(GetWorld(), MainUIBP);
		PlayerUI = Cast<URPGMainUserWidget>(Widget);

		ensure(PlayerUI);

		PlayerUI->Init();
		PlayerUI->AddToViewport();
	}
}

void AUIManager::ShowUI(ERPG_UI Type)
{
	URPGUserWidget* UserWidget = GetRPGUI(Type);
	if (!UserWidget) { return; }

	if (UIList.Num() > 0)
	{
		ERPG_UI TopUIType = UIList[0];
		GetCanvasPanel(TopUIType)->SetZOrder(PopupZOrder);
	}

	if (UIList.Contains(Type))
	{
		int index = UIList.IndexOfByKey(Type);
		UIList.RemoveAt(index);
	}
	UIList.Insert(Type, 0);

	UCanvasPanelSlot* Current = GetCanvasPanel(UserWidget->UI_Type);
	Current->SetZOrder(TopZOrder);

	if (UserWidget->GetVisibility() == ESlateVisibility::Collapsed)
	{
		UserWidget->SetVisibility(ESlateVisibility::Visible);
		UserWidget->ShowInitUI();
		UserWidget->RefreshUI();
	}
}



void AUIManager::HideUI(ERPG_UI Type)
{
	URPGUserWidget* UserWidget = GetRPGUI(Type);
	if (!UserWidget) { return; }

	if (UIList.Contains(Type))
	{
		int index = UIList.IndexOfByKey(Type);
		UIList.RemoveAt(index);
	}

	if (UIList.Num() > 0)
	{
		ERPG_UI TopUIType = UIList[0];
		GetCanvasPanel(TopUIType)->SetZOrder(TopZOrder);
	}

	UserWidget->HideSetUI();
	UserWidget->SetVisibility(ESlateVisibility::Collapsed);

}

void AUIManager::TopHideUI()
{
	if (UIList.Num() > 0)
	{
		ERPG_UI TopUIType = UIList[0];
		HideUI(TopUIType);
	}
}

UCanvasPanelSlot* AUIManager::GetCanvasPanel(ERPG_UI Type)
{
	return PlayerUI->GetCanvasPanel(Type);
}

void AUIManager::PlayerGoodsUIRefresh()
{
	PlayerUI->PlayerGoodsRefresh();
}

void AUIManager::ShowItemBox(FVector2D SpawnPos, ShowBoxData Data)
{
	PlayerUI->ShowItemInfoBox(SpawnPos ,Data);
}

void AUIManager::HideItemBox()
{
	PlayerUI->HideItemInfoBox();
}

void AUIManager::RefreshUI(ERPG_UI UIType)
{
	PlayerUI->RPGUIRefresh(UIType);
}


URPGUserWidget* AUIManager::GetRPGUI(ERPG_UI UIType)
{
	return PlayerUI->GetRPGUI(UIType);
}

bool AUIManager::IsShowUI(ERPG_UI UIType)
{
	if (UIList.Contains(UIType))
	{
		return true;
	}

	return false;
}

void AUIManager::GetRPGUIToggle(ERPG_UI UIType)
{
	if (IsShowUI(UIType))
	{
		HideUI(UIType);
	}
	else
	{
		ShowUI(UIType);
	}
}


