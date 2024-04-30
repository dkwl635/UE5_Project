// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RPGMainUserWidget.h"

void URPGMainUserWidget::OpenInventoryUI()
{
	UE_LOG(LogTemp, Warning, TEXT("OpenInventoryUI"));
	
    if (!InventoryUI)
    {
        return;
    }

    UUserWidget* WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), InventoryUI);

    if (WidgetInstance)
    {
        // ºäÆ÷Æ®¿¡ À§Á¬ Ãß°¡
        WidgetInstance->AddToViewport();
    }
}
