// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RPGMainUserWidget.h"



void URPGMainUserWidget::NativeConstruct()
{
    Super::NativeConstruct();

    for (int i = 0; i < UICreatList.Num(); i++)
    {
        UUserWidget* NewUserWidget = CreateWidget(GetWorld(), UICreatList[i].UIClass);

        if (RPGUIMap.Contains(UICreatList[i].UIType))
        {
            ensure(false);
            continue;
        }

        RPGUIMap.Add(UICreatList[i].UIType, NewUserWidget);

    }
    

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

UUserWidget* URPGMainUserWidget::GetRPGUI(ERPG_UI UI_Type)
{
    if (RPGUIMap.Contains(UI_Type))
        return RPGUIMap[UI_Type];

    return nullptr;
}

