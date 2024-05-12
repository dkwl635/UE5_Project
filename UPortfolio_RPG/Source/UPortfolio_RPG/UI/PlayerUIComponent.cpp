// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/PlayerUIComponent.h"
#include "Blueprint/UserWidget.h"
#include "UI/RPGMainUserWidget.h"

// Sets default values for this component's properties
UPlayerUIComponent::UPlayerUIComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UPlayerUIComponent::BeginPlay()
{
	Super::BeginPlay();

	return;
	if (PlayerUserWidget)
	{
		auto Widget = CreateWidget<UUserWidget>(GetWorld(), PlayerUserWidget);
		PlayerUI = Cast<URPGMainUserWidget>(Widget);

		ensure(PlayerUI);

		PlayerUI->Init();
		PlayerUI->AddToViewport();
	}
	
}

