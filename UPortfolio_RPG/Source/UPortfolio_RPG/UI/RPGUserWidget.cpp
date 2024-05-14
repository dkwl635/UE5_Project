// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RPGUserWidget.h"
#include "Components/CanvasPanelSlot.h"

void URPGUserWidget::RefreshUI()
{
}

void URPGUserWidget::Init()
{
}

void URPGUserWidget::ShowInitUI()
{
}

void URPGUserWidget::HideSetUI()
{
}



UCanvasPanelSlot* URPGUserWidget::GetCanvasPanelSlot()
{
    if (!CanvasPaneSlot)
    {
        if (Slot)
        {
            UCanvasPanelSlot* NewCanvasPanelSlot = Cast<UCanvasPanelSlot>(Slot);
            CanvasPaneSlot = NewCanvasPanelSlot;
        }
    }

   

    return CanvasPaneSlot;
}

