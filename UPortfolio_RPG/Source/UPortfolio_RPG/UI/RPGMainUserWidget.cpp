// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RPGMainUserWidget.h"
#include "UI/RPGSlotUserWidget.h"
#include "UI/Slot/SlotData.h"
#include "Item/PlayerInventorySubsystem.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/CanvasPanel.h"
#include "UIEnum.h"
#include "UI/ItemInfoUserWdiget.h"
#include "Item/ItemData.h"
#include "Math/UnrealMathUtility.h"

TWeakObjectPtr<UPlayerInventorySubsystem> URPGMainUserWidget::GetPlayerInven()
{
    PlayerInven = GetGameInstance()->GetSubsystem<UPlayerInventorySubsystem>();
    return PlayerInven;
}

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
    GetRPGUI(ERPG_UI::EQUIPMENT)->SetVisibility(ESlateVisibility::Collapsed);

    //ZOreder Setting
    GetCanvasPanel(ERPG_UI::QUICKSLOTS)->SetZOrder(HUDZOrder);
    PlayerGoodsRefresh();

    ItemBox = Cast<UItemInfoUserWdiget>(ItemBoxPanel->GetChildAt(0));
    ItemBoxPanel->SetVisibility(ESlateVisibility::Collapsed);
    ItemBoxPanelSlot = Cast<UCanvasPanelSlot>(ItemBoxPanel->Slot);

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
        if (UserWidget->GetVisibility() == ESlateVisibility::Collapsed)
        {
            UserWidget->SetVisibility(ESlateVisibility::Visible);
            UserWidget->ShowInitUI();
            UserWidget->RefreshUI();
       }
 
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
        UserWidget->HideSetUI();
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

URPGUserWidget* URPGMainUserWidget::RPGUIRefresh(ERPG_UI Type)
{
    auto UI = GetRPGUI(Type);
    if (UI->GetVisibility() == ESlateVisibility::Collapsed)
    {
        return nullptr;
    }

    UI->RefreshUI();

    return UI;
}

void URPGMainUserWidget::PlayerGoodsRefresh()
{
    int32 PlayerGold = GetPlayerInven()->GetPlayerGold();
    int32 PlayerCoin = GetPlayerInven()->GetPlayerCoin();

    GoldTextBlock->SetText(FText::AsNumber(PlayerGold));
    CoinTextBlock->SetText(FText::AsNumber(PlayerCoin));
}

void URPGMainUserWidget::ShowItemInfoBox(FVector2D SpawnPos , FItemData* Data)
{
    ItemBoxPanel->SetVisibility(ESlateVisibility::HitTestInvisible);
    FVector2D Pos = GetShowItemPos(SpawnPos);
    ItemBoxPanelSlot->SetPosition(Pos);
    ItemBox->ShowItemInfo(Data);
}

void URPGMainUserWidget::HideItemInfoBox()
{
    ItemBoxPanel->SetVisibility(ESlateVisibility::Collapsed);
}

FVector2D URPGMainUserWidget::GetShowItemPos(FVector2D SppawnPos)
{
   FVector2D SlotSize =  ItemBoxPanelSlot->GetSize();
   FVector2D NewPos = FVector2D::Zero();
   NewPos.X = ViewSize.X - SlotSize.X;
   NewPos.Y = ViewSize.Y - SlotSize.Y;

   NewPos.X = FMathf::Clamp(SppawnPos.X, 0, NewPos.X);
   NewPos.Y = FMathf::Clamp(SppawnPos.Y, 0, NewPos.Y);

    return NewPos;
}




