// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIManager.h"
#include "UI/RPGMainUserWidget.h"
#include "Item/ItemData.h"


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


