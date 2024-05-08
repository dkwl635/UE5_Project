// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RPGMainUserWidget.h"
#include "UI/RPGSlotUserWidget.h"
#include "UI/Slot/SlotData.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "UIEnum.h"

void URPGMainUserWidget::Init()
{

    int UICount = RPGUI->GetChildrenCount();
    for (int i = 0; i < UICount; i++)
    {
        UCanvasPanel* widget = Cast<UCanvasPanel>( RPGUI->GetChildAt(i));
        URPGUserWidget* UI =  Cast<URPGUserWidget>(widget->GetChildAt(0));
        UI->Init();
        RPGUIMap.Add(UI->UI_Type, UI);
        RPGUICanvasMap.Add(UI->UI_Type, widget);
        
    }


    /*QuickSlotsUI->Init();
    InventoryUI->Init();
    ShopUI->Init();*/

    //auto pos  = InventoryUI->
    GetRPGUI(ERPG_UI::INVENTORY)->SetVisibility(ESlateVisibility::Hidden);
    GetRPGUI(ERPG_UI::SHOP)->SetVisibility(ESlateVisibility::Hidden);
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
        //UserWidget->AddToViewport();
        UserWidget->SetVisibility(ESlateVisibility::Visible);
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

URPGUserWidget* URPGMainUserWidget::GetRPGUI(ERPG_UI Type)
{
    if (RPGUIMap.Contains(Type))
    {
        return RPGUIMap[Type];
    }

    return nullptr;
}

UCanvasPanel* URPGMainUserWidget::GetCanvasPanel(ERPG_UI Type)
{
    if (RPGUICanvasMap.Contains(Type))
    {
        return RPGUICanvasMap[Type];
    }

    return nullptr;
}




