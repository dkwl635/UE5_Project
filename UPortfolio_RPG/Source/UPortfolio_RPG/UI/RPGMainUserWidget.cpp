// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RPGMainUserWidget.h"
#include "UI/RPGSlotUserWidget.h"
#include "UI/Slot/SlotData.h"


void URPGMainUserWidget::Init()
{

    InventoryUI->Init();
    QuickSlotsUI->Init();

    //auto pos  = InventoryUI->
    InventoryUI->RemoveFromViewport();
}

URPGMainUserWidget::~URPGMainUserWidget()
{
    

    RPGUIMap.Empty();
}

void URPGMainUserWidget::ShowUI(UUserWidget* UserWidget)
{
    if (!UserWidget) { return; }
    if (!UserWidget->IsInViewport())
    {
        // ºäÆ÷Æ®¿¡ À§Á¬ Ãß°¡
        UserWidget->AddToViewport();
    }
   

}

void URPGMainUserWidget::HideUI(UUserWidget* UserWidget)
{
    if (!UserWidget) { return; }
    if (UserWidget->IsInViewport())
    {
        UserWidget->RemoveFromParent();
    }
 
}

void URPGMainUserWidget::ToggleUI(UUserWidget* UserWidget)
{
    if (!UserWidget) { return; }

    if (!UserWidget->IsInViewport())
    {
        // ºäÆ÷Æ®¿¡ À§Á¬ Ãß°¡
        ShowUI(UserWidget);
    }
    else
    {
        HideUI(UserWidget);
    }
}

URPGUserWidget* URPGMainUserWidget::GetRPGUI(ERPG_UI UI_Type)
{
    switch (UI_Type)
    {
    case ERPG_UI::NONE:
        break;
    case ERPG_UI::INVENTORY:
        return InventoryUI;
    case ERPG_UI::QUICKSLOTS:
        return QuickSlotsUI;
    default:
        break;
    }

    return nullptr;
}

