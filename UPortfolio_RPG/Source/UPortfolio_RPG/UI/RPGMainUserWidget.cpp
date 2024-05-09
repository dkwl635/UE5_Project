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
        UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(widget->Slot);
        UI->Init();
        RPGUIMap.Add(UI->UI_Type, UI);
        RPGUICanvasMap.Add(UI->UI_Type, CanvasSlot);
        
    }

    GetRPGUI(ERPG_UI::INVENTORY)->SetVisibility(ESlateVisibility::Collapsed);
    GetRPGUI(ERPG_UI::SHOP)->SetVisibility(ESlateVisibility::Collapsed);

    //ZOreder Setting
    GetCanvasPanel(ERPG_UI::QUICKSLOTS)->SetZOrder(HUDZOrder);
}

URPGMainUserWidget::~URPGMainUserWidget()
{
   
    RPGUIMap.Empty();
}

void URPGMainUserWidget::ShowUI(URPGUserWidget* UserWidget)
{
    if (!UserWidget) { return; }
    if (!UserWidget->IsInViewport())
    {
        
        //UserWidget->AddToViewport();
        if (TopPopupUI.IsValid())
        {
            TopPopupUI.Get()->SetZOrder(PopupZOrder);
        }
       
        UCanvasPanelSlot* Current = GetCanvasPanel(UserWidget->UI_Type);
        Current->SetZOrder(TopZOrder);
        TopPopupUI = Current;
        UserWidget->SetVisibility(ESlateVisibility::Visible);
        UserWidget->RefreshUI();
    }
   

}

void URPGMainUserWidget::ShowUI(ERPG_UI Type)
{
    ShowUI(GetRPGUI(Type));
}

void URPGMainUserWidget::HideUI(URPGUserWidget* UserWidget)
{
    if (!UserWidget) { return; }
    if (UserWidget->IsInViewport())
    {
        UserWidget->SetVisibility(ESlateVisibility::Collapsed);
    }
 
}

void URPGMainUserWidget::ToggleUI(URPGUserWidget* UserWidget)
{
    if (!UserWidget) { return; }

    if (!UserWidget->IsInViewport())
    {
        
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

UCanvasPanelSlot* URPGMainUserWidget::GetCanvasPanel(ERPG_UI Type)
{
    if (RPGUICanvasMap.Contains(Type))
    {
        return RPGUICanvasMap[Type];
    }

    return nullptr;
}




