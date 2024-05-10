// Fill out your copyright notice in the Description page of Project Settings.
#include "UI/RPGShop.h"
#include "Kismet/GameplayStatics.h"
#include "DataSubsystem/DataSubsystem.h"
#include "Components/UniformGridPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "UI/Slot/ShopBuySlot.h"
#include "UI/PlayerUIComponent.h"
#include "UI/RPGMainUserWidget.h"
#include "Item/ItemData.h"
#include "Item/PlayerInventorySubsystem.h"

void URPGShop::Init()
{
	auto SlotList = BuyItemPanel->GetSlots();

	for (int i = 0; i < SlotList.Num(); i++)
	{
		auto content = SlotList[i]->Content.Get();
		UShopBuySlot* ShopSlot = Cast<UShopBuySlot>(content);
		ShopSlot->Init();
		BuyShopSlotList.Add(ShopSlot);
		ShopSlot->ShopHelper = this;
	}

}

void URPGShop::RefreshUI()
{

}

void URPGShop::SetShopData(TArray<FShopBuyItemData> ShopList)
{
	UDataSubsystem* DataTable = GetGameInstance()->GetSubsystem<UDataSubsystem>();
	int SlotCount = BuyShopSlotList.Num();
	for (int i = 0; i < SlotCount; i++)
	{
		UShopBuySlot* ShopSlot = BuyShopSlotList[i].Get();
		if (i >= ShopList.Num())
		{
			ShopSlot->SetVisibility(ESlateVisibility::Collapsed);
			continue;
		}
		else
		{
			FShopBuyItemData Data = ShopList[i];
			FItemData* buyItem = DataTable->FindItem(Data.ItemInfo.RowName);
			int32 Price = Data.Price;
			int32 Count = Data.Count;

			ShopSlot->SetShopBuySlot(buyItem, Data.ItemInfo.RowName,Price, Count);
			ShopSlot->RefreshUI();
		}
	}

}

void URPGShop::BuyItem(UShopBuySlot* ShopSlot)
{
		UPlayerInventorySubsystem* PlayerInven = GetGameInstance()->GetSubsystem<UPlayerInventorySubsystem>();

		bool bBuy = PlayerInven->AddItem(ShopSlot->ItemRowName, ShopSlot->BuyCount);
		GetPlayerUI()->GetRPGUI(ERPG_UI::INVENTORY)->RefreshUI();
}

URPGMainUserWidget* URPGShop::GetPlayerUI()
{
	if (!PlayerUI.IsValid())
	{
		auto PlayerControll = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		//	UPlayerUIComponent* Find = (UPlayerUIComponent*)(PlayerControll->GetPawn()->GetComponentByClass(UPlayerUIComponent::StaticClass()));
		UPlayerUIComponent* Find = PlayerControll->GetPawn()->FindComponentByClass<UPlayerUIComponent>();
		PlayerUI = Find->PlayerUI;
	}

	return PlayerUI.Get();

}
