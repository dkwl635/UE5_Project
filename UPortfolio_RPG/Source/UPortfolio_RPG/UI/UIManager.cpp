// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIManager.h"
#include "UI/RPGMainUserWidget.h"
TWeakObjectPtr<AUIManager> AUIManager::UIManager = nullptr;
// Sets default values
AUIManager::AUIManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	///Script/UMGEditor.WidgetBlueprint'/Game/KJW/UI/BPUI_MainUI.BPUI_MainUI'
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

//// Called every frame
//void AUIManager::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}
//
