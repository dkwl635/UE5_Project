// Fill out your copyright notice in the Description page of Project Settings.
#include "PlayerInventorySubsystem.h"
#include "DataSubsystem/DataSubsystem.h"
#include "Item/Item.h"
#include "UI/RPGSlot.h"
#include "UI/UIManager.h"
#include "UI/UIEnum.h"
#include "Json.h"
#include "JsonUtilities.h"

UPlayerInventorySubsystem* UPlayerInventorySubsystem::PlayerInventorySubsystem = nullptr;
int32 UPlayerInventorySubsystem::GetPlayerCoin()
{
	return PlayerCoin;
}

int32 UPlayerInventorySubsystem::GetPlayerGold()
{
	return PlayerGold;
}

int32 UPlayerInventorySubsystem::GetEnchantStone()
{
	return EnchantStone;
}

void UPlayerInventorySubsystem::SetPlayerCoin(int32 Value)
{
	PlayerCoin = Value;
	AUIManager::UIManager->PlayerGoodsUIRefresh();
}

void UPlayerInventorySubsystem::SetPlayerGold(int32 Value)
{
	PlayerGold = Value;
	AUIManager::UIManager->PlayerGoodsUIRefresh();
}

void UPlayerInventorySubsystem::SetPlayerEnchantStone(int32 Value)
{
	EnchantStone = Value;
	AUIManager::UIManager->PlayerGoodsUIRefresh();
}

UPlayerInventorySubsystem::UPlayerInventorySubsystem()
{

}

UPlayerInventorySubsystem::~UPlayerInventorySubsystem()
{
	PlayerInventorySubsystem = nullptr;
}

void UPlayerInventorySubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	PlayerInventorySubsystem = this;

	NormalInventory.Init(nullptr, MaxInvenSize);
	GearInventory.Init(nullptr, MaxInvenSize);
	EquipmentInventory.Init(nullptr,7);
	QuickItemSlotsPointer.Init(-1, 8);

	DataSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDataSubsystem>();
	if (ItemClass) { ItemClass = UItem::StaticClass()->GetDefaultObject<UItem>(); }

	//Load
	Load();

}

bool UPlayerInventorySubsystem::Init()
{	
	return true;
}

void UPlayerInventorySubsystem::AddInitItem(const FName& InKey, int Count, int8 Index)
{
	FItemData* Data = DataSubsystem->FindItem(InKey);
	
	if (Data->ItemType == EITEMTYPE::COIN)
	{
		SetPlayerCoin(GetPlayerCoin() + Count);
		return;
	}
	else 	if (Data->ItemType == EITEMTYPE::GOLD)
	{
		SetPlayerGold(GetPlayerGold() + Count);
		return;
	}



	Inventory Inventory = GetInventory(Data->ItemType);
	TSharedPtr<FItemData> NewItemData = MakeShared<FItemData>(*Data);
	NewItemData->CurrentBundleCount = Count;
	(*Inventory)[Index] = NewItemData;
}

bool UPlayerInventorySubsystem::AddItem(const FName& InKey, int Count)
{
	FItemData* Data = DataSubsystem->FindItem(InKey);
	if (!Data) { return false; }

	if (Data->ItemType == EITEMTYPE::COIN)
	{
		SetPlayerCoin(GetPlayerCoin() + Count);
		return true ;
	}
	else 	if (Data->ItemType == EITEMTYPE::GOLD)
	{
		SetPlayerGold(GetPlayerGold() + Count);
		return true;
	}


	Inventory Inventory = GetInventory(Data->ItemType);

	if (!IsAddable(Inventory ,Data, Count)) { return false; }

	MoveItemToInventory(Inventory, Data, Count);

	return	true;
}

bool UPlayerInventorySubsystem::IsAddable(Inventory Inventory,FItemData* ItemData, int8 Count)
{
	
	FName ItemName = ItemData->ItemName;
	int8 RemainingCount = Count;
	int8 InvenSize = MaxInvenSize;
	int8 CheckInvenIndex = FindItemInInventory(Inventory,ItemName, 0);

	while (CheckInvenIndex < InvenSize)
	{
		if (CheckInvenIndex >= InvenSize) { break; }
		
		int EmptySize = (*Inventory)[CheckInvenIndex]->MaxBundleCount - (*Inventory)[CheckInvenIndex]->CurrentBundleCount;

		RemainingCount -= EmptySize;
		if (RemainingCount <= 0) { return  true; }
		CheckInvenIndex = FindItemInInventory(Inventory,ItemName, CheckInvenIndex + 1);
	}
		
	int8 EmptyIndex = FindEmptyInventory(Inventory,0);

	while (EmptyIndex < InvenSize)
	{
		RemainingCount -= ItemData->MaxBundleCount;
		if (RemainingCount <= 0) { return  true; }

		EmptyIndex = FindEmptyInventory(Inventory,EmptyIndex+1);
	}

	if (RemainingCount <= 0) { return  true; }

	return false;
}

int8 UPlayerInventorySubsystem::FindItemInInventory(Inventory Inventory, const FName& ItemName, int8 StartIndex = 0)
{
	int8 Size = MaxInvenSize;
	for (int8 i = StartIndex; i < Size; i++)
	{
		TSharedPtr<FItemData> ItemData = (*Inventory)[i];
		if (ItemData == nullptr) { continue; }
		if (ItemData->ItemName == ItemName) 
		{
			if (ItemData->CurrentBundleCount < ItemData->MaxBundleCount) { return i; }
		
			continue;
		}
	}
	return Size;
}

int8 UPlayerInventorySubsystem::FindEmptyInventory(Inventory Inventory , int8 StartIndex = 0)
{
	int8 Size = MaxInvenSize;
	for (int8 i = StartIndex; i < Size; i++)
	{
		if ((*Inventory)[i] == nullptr) { return i; }
	}
	return Size;
}

bool UPlayerInventorySubsystem::MoveItemToInventory(Inventory Inventory ,FItemData* ItemData, int8 Count)
{	
	FName ItemName = ItemData->ItemName;
	int8 RemainingCount = Count;	
	int8 InvenSize = MaxInvenSize;
	int8 CheckInvenIndex = FindItemInInventory(Inventory,ItemName);
	while (CheckInvenIndex < InvenSize)
	{
		if (CheckInvenIndex >= InvenSize) { break; }
			
		int8 EmptySize = (*Inventory)[CheckInvenIndex]->MaxBundleCount - (*Inventory)[CheckInvenIndex]->CurrentBundleCount;
		if (EmptySize > 0)
		{
			int8 AddCount = 0;
			if (EmptySize > RemainingCount)
			{
				AddCount = RemainingCount;
				RemainingCount = 0;
			}
			else if (EmptySize <= RemainingCount)
			{
				AddCount = EmptySize;
				RemainingCount -= AddCount;
			}
			(*Inventory)[CheckInvenIndex]->CurrentBundleCount += AddCount;
		}

		if (RemainingCount <= 0) { return  true; }
	
		CheckInvenIndex = FindItemInInventory(Inventory, ItemName , CheckInvenIndex+1);
	}

	int8 EmptyIndex = FindEmptyInventory(Inventory);
	while (EmptyIndex < InvenSize)
	{
		int8 AddCount = 0;
		if (ItemData->MaxBundleCount > RemainingCount)
		{
			AddCount = RemainingCount;
			RemainingCount = 0;
		}
		else if (ItemData->MaxBundleCount <= RemainingCount)
		{
			AddCount = ItemData->MaxBundleCount;
			RemainingCount -= AddCount;
		}
		
		TSharedPtr<FItemData> NewItemData = MakeShared<FItemData>(*ItemData);
		NewItemData->CurrentBundleCount = AddCount;
		(*Inventory)[EmptyIndex] = NewItemData;

		if (RemainingCount <= 0) { return  true; }
		EmptyIndex = FindEmptyInventory(Inventory , EmptyIndex+1);
	}
	return false;
}

void UPlayerInventorySubsystem::RefreshUI(ERPG_UI UIType)
{
	AUIManager::UIManager->RefreshUI(UIType);
}

void UPlayerInventorySubsystem::UseItem(EITEMTYPE ItemType, int8 InventoryIndex , int8 Count)
{
	Inventory Inventory = GetInventory(ItemType);

	if (!Inventory || Count <= 0) { return; }
	
	FItemData* data = (*Inventory)[InventoryIndex].Get();
	if(!data) { return; }
	

	int NewCount = (data->CurrentBundleCount - Count);
	if (NewCount <= 0)
	{
		(*Inventory)[InventoryIndex] = nullptr;

		if (int QuickSlotIndex = CheckQuickSlotItem(InventoryIndex) != -1)
		{
			QuickItemSlotsPointer[QuickSlotIndex] = -1;
		}

	}
	else { data->CurrentBundleCount = NewCount; }

	RefreshUI(ERPG_UI::QUICKSLOTS);
	RefreshUI(ERPG_UI::INVENTORY);
	UseItem(data, Count);
	GEngine->ForceGarbageCollection(true);
}

void UPlayerInventorySubsystem::RemoveItem(EITEMTYPE ItemType, int8 InventoryIndex, int8 Count)
{
	Inventory Inventory = GetInventory(ItemType);

	if (!Inventory || Count <= 0) { return; }

	(*Inventory)[InventoryIndex] = nullptr;
	GEngine->ForceGarbageCollection(true);

	if (ItemType != EITEMTYPE::GEAR)
	{
		int QuickSlot = CheckQuickSlotItem(InventoryIndex);
		if (QuickSlot != -1)
		{
			QuickSlotClear(QuickSlot);
			AUIManager::UIManager->RefreshUI(ERPG_UI::QUICKSLOTS);
		}
	}

	AUIManager::UIManager->RefreshUI(ERPG_UI::INVENTORY);
}


void UPlayerInventorySubsystem::UseItem(FItemData* ItemData, int8 Count)
{
	ItemClass->UseItem(ItemData);
}

TWeakPtr<FItemData> UPlayerInventorySubsystem::GetItemInfo(EITEMTYPE ItemType, int8 InventoryIndex)
{
	Inventory Inventory = GetInventory(ItemType);
	if (InventoryIndex < 0 || !Inventory) { return nullptr; }

	return (*Inventory)[InventoryIndex];
}

void UPlayerInventorySubsystem::SwapItem(EITEMTYPE ItemType, int8 Index1, int8 Index2)
{
	Inventory Inventory = GetInventory(ItemType);

	TSharedPtr<FItemData>& thisItemData = (*Inventory)[Index1];
	TSharedPtr<FItemData>& StartItemData = (*Inventory)[Index2];

	
	
	bool bSwap = false;
	bool bCombine = false;
	if (thisItemData != nullptr && StartItemData != nullptr)
	{
		if (thisItemData->Unique_ID == StartItemData->Unique_ID)
		{
			if(CombineItem(ItemType, Index1, Index2) )
			{
				//bCombine = true;
			}
		}
		else { bSwap = true; }
	}
	else { bSwap = true; }

	if (bSwap)
	{
		Swap(thisItemData, StartItemData);	
		if (ItemType != EITEMTYPE::GEAR)
		{
			int QuickSlotIndex1 = CheckQuickSlotItem(Index1);
			int QuickSlotIndex2 = CheckQuickSlotItem(Index2);

			if (QuickSlotIndex1 != -1) { SetAttachQuickSlot(QuickSlotIndex1, Index2); }
			if (QuickSlotIndex2 != -1) { SetAttachQuickSlot(QuickSlotIndex2, Index1); }
		}
	}

	AUIManager::UIManager->RefreshUI(ERPG_UI::QUICKSLOTS);
}

bool UPlayerInventorySubsystem::CombineItem(EITEMTYPE ItemType ,int8 Index1, int8 Index2)
{
	Inventory Inventory = GetInventory(ItemType);

	TSharedPtr<FItemData>& ItemData1 = (*Inventory)[Index1];
	TSharedPtr<FItemData>& ItemData2 = (*Inventory)[Index2];

	if (ItemData1->Unique_ID == ItemData2->Unique_ID)
	{
		if (ItemData1->CurrentBundleCount == ItemData1->MaxBundleCount) { return false; }

		if (ItemData1->CurrentBundleCount < ItemData1->MaxBundleCount)
		{
			int8 temp = ItemData1->CurrentBundleCount + ItemData2->CurrentBundleCount;
			if (temp <= ItemData1->MaxBundleCount)
			{
				ItemData1->CurrentBundleCount = temp;
				ItemData2 = nullptr;
			}
			else
			{
				ItemData1->CurrentBundleCount = ItemData1->MaxBundleCount;
				ItemData2->CurrentBundleCount = temp - ItemData1->MaxBundleCount;
			}
		}
	}
	return true;
}

void UPlayerInventorySubsystem::AddInitGear(const FName& InKey, EGEARTYPE GearType)
{
	FItemData* Data = DataSubsystem->FindItem(InKey);
	TSharedPtr<FItemData> NewItemData = MakeShared<FItemData>(*Data);

	NewItemData->CurrentBundleCount = 1;
	EquipmentInventory[(int)GearType] = NewItemData;
}

FItemData* UPlayerInventorySubsystem::ChangeGear(EGEARTYPE GearType,int8 Index)
{
	FItemData* OrginData = (EquipmentInventory[(int)GearType]).Get();
	
	TSharedPtr<FItemData>& NewGear =  GearInventory[Index];
	TSharedPtr<FItemData>& OldGear = EquipmentInventory[(int)GearType];

	Swap(NewGear, OldGear);

	RefreshUI(ERPG_UI::EQUIPMENT);
	RefreshUI(ERPG_UI::INVENTORY);

	return OrginData;
}

bool UPlayerInventorySubsystem::DeEquipment(EGEARTYPE GearType)
{
	TSharedPtr<FItemData>& OldGear = EquipmentInventory[(int)GearType];

	int InvenIndex = FindEmptyInventory(GetInventory(EITEMTYPE::GEAR) ,  0);
	if (InvenIndex >= MaxInvenSize) { return false; }

	ChangeGear(GearType, InvenIndex);
	RefreshUI(ERPG_UI::INVENTORY);
	RefreshUI(ERPG_UI::EQUIPMENT);
	return  true;
}

FItemData* UPlayerInventorySubsystem::GetNormalItem(int8 InvenIndex)
{
	return NormalInventory[InvenIndex].Get();
}

FItemData* UPlayerInventorySubsystem::GetGearItem(int8 InvenIndex)
{
	return GearInventory[InvenIndex].Get();
}

FItemData* UPlayerInventorySubsystem::GetEquipmentItem(int8 InvenIndex)
{
	return EquipmentInventory[InvenIndex].Get();
}

TArray<TSharedPtr<FItemData>>* UPlayerInventorySubsystem::GetInventory(EITEMTYPE ItemType)
{
	if (ItemType == EITEMTYPE::GEAR) { return &GearInventory; }
	else { return &NormalInventory; }
}

int32 UPlayerInventorySubsystem::GetPlayerAddAttack()
{
	int32 Result = 0;
	for (int i = 0; i < EquipmentInventory.Num(); i++)
	{
		if (!EquipmentInventory[i]){continue;}

		FGearData* data  = DataSubsystem->FindGearData( EquipmentInventory[i]->StatusData.RowName);
		if (data->EStat == ESTAT::ATK)
		{
			Result += data->GearValue;
		}
	}

	return Result;
}

int32 UPlayerInventorySubsystem::GetPlayerAddMaxHp()
{
	int32 Result = 0;
	for (int i = 0; i < EquipmentInventory.Num(); i++)
	{
		if (!EquipmentInventory[i]) { continue; }

		FGearData* data = DataSubsystem->FindGearData(EquipmentInventory[i]->StatusData.RowName);
		if (data->EStat == ESTAT::HP)
		{
			Result += data->GearValue;
		}
	}

	return Result;
}

void UPlayerInventorySubsystem::Save()
{
	//Inventory
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetNumberField(TEXT("Gold"), PlayerGold);
	JsonObject->SetNumberField(TEXT("Coin"), PlayerCoin);
	JsonObject->SetNumberField(TEXT("EnchantStone"), EnchantStone);

	//GearInventory
	TArray<TSharedPtr<FJsonValue>> GearItemJsonArray;
	int Size = GearInventory.Num();
	for (int i = 0; i < Size; i++)
	{
		if(GearInventory[i].IsValid()){
			
			TSharedPtr<FJsonObject> JsonIteemObject = MakeShareable(new FJsonObject());
			JsonIteemObject->SetStringField(TEXT("RowName"), GearInventory[i]->RowName.ToString());
			JsonIteemObject->SetNumberField(TEXT("SlotIndex"), i);
			JsonIteemObject->SetNumberField(TEXT("Count"), GearInventory[i]->CurrentBundleCount);
			GearItemJsonArray.Add(MakeShareable(new FJsonValueObject(JsonIteemObject)));
		}
	}
	JsonObject->SetArrayField(TEXT("GearItem"), GearItemJsonArray);
	//NormalInventory
	TArray<TSharedPtr<FJsonValue>> NormalItemJsonArray;
	 Size = NormalInventory.Num();
	for (int i = 0; i < Size; i++)
	{
		if (NormalInventory[i].IsValid()) {

			TSharedPtr<FJsonObject> JsonIteemObject = MakeShareable(new FJsonObject());
			JsonIteemObject->SetStringField(TEXT("RowName"), NormalInventory[i]->RowName.ToString());
			JsonIteemObject->SetNumberField(TEXT("SlotIndex"), i);
			JsonIteemObject->SetNumberField(TEXT("Count"), NormalInventory[i]->CurrentBundleCount);
			NormalItemJsonArray.Add(MakeShareable(new FJsonValueObject(JsonIteemObject)));
		}
	}
	JsonObject->SetArrayField(TEXT("NormalItem"), NormalItemJsonArray);
	//EquipmentInventory
	TArray<TSharedPtr<FJsonValue>> EquipmentJsonArray;
	Size = EquipmentInventory.Num();
	for (int i = 0; i < Size; i++)
	{
		if (EquipmentInventory[i].IsValid()) {

			TSharedPtr<FJsonObject> JsonIteemObject = MakeShareable(new FJsonObject());
			JsonIteemObject->SetStringField(TEXT("RowName"), EquipmentInventory[i]->RowName.ToString());
			JsonIteemObject->SetNumberField(TEXT("GearType"), i);
			EquipmentJsonArray.Add(MakeShareable(new FJsonValueObject(JsonIteemObject)));
		}
	}
	JsonObject->SetArrayField(TEXT("Equipment"), EquipmentJsonArray);

	//QuickSlot
	JsonObject->SetNumberField(TEXT("QuickItemSlot1"), QuickItemSlotsPointer[0]);
	JsonObject->SetNumberField(TEXT("QuickItemSlot2"), QuickItemSlotsPointer[1]);
	JsonObject->SetNumberField(TEXT("QuickItemSlot3"), QuickItemSlotsPointer[2]);
	JsonObject->SetNumberField(TEXT("QuickItemSlot4"), QuickItemSlotsPointer[3]);

 	FString OutputString;
 	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);

	if (FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer))
	{
		FString FilePath = FPaths::ProjectDir() / TEXT("SaveData/SaveData.json");
		
		if (FFileHelper::SaveStringToFile(OutputString, *FilePath))
		{
			UE_LOG(LogTemp, Warning, TEXT("Successfully saved JSON to file"));
		}	
	}



}

void UPlayerInventorySubsystem::Load()
{
	FString FilePath = FPaths::ProjectDir() / TEXT("SaveData/SaveData.json");
	FString JsonString;

	if (FFileHelper::LoadFileToString(JsonString, *FilePath))
	{
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
		TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

		if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
		{
			PlayerGold = JsonObject->GetNumberField("Gold");
			PlayerCoin = JsonObject->GetNumberField("Coin");
			EnchantStone = JsonObject->GetNumberField("EnchantStone");

			//GearItem
			const TArray<TSharedPtr<FJsonValue>>* GearJsonArray;
			if (JsonObject->TryGetArrayField(TEXT("GearItem"), GearJsonArray))
			{
				for (const TSharedPtr<FJsonValue>& JsonValue : *GearJsonArray)
				{
					TSharedPtr<FJsonObject> ItemObject = JsonValue->AsObject();
					if (ItemObject.IsValid())
					{
						FName RowName = FName(ItemObject->GetStringField(TEXT("RowName")));
						int8 SlotIndex = ItemObject->GetNumberField(TEXT("SlotIndex"));
						int8 Count = ItemObject->GetNumberField(TEXT("Count"));

						AddInitItem(RowName, Count, SlotIndex);
					}
				}
			}
			//NormalItem
			const TArray<TSharedPtr<FJsonValue>>* NormalJsonArray;
			if (JsonObject->TryGetArrayField(TEXT("NormalItem"), NormalJsonArray))
			{
				for (const TSharedPtr<FJsonValue>& JsonValue : *NormalJsonArray)
				{
					TSharedPtr<FJsonObject> ItemObject = JsonValue->AsObject();
					if (ItemObject.IsValid())
					{
						FName RowName = FName(ItemObject->GetStringField(TEXT("RowName")));
						int8 SlotIndex = ItemObject->GetNumberField(TEXT("SlotIndex"));
						int8 Count = ItemObject->GetNumberField(TEXT("Count"));

						AddInitItem(RowName, Count, SlotIndex);
					}
				}
			}
			//EquipmentInventory
			const TArray<TSharedPtr<FJsonValue>>* EquipmentJsonArray;
			if (JsonObject->TryGetArrayField(TEXT("Equipment"), EquipmentJsonArray))
			{
				for (const TSharedPtr<FJsonValue>& JsonValue : *EquipmentJsonArray)
				{
					TSharedPtr<FJsonObject> ItemObject = JsonValue->AsObject();
					if (ItemObject.IsValid())
					{
						FName RowName = FName(ItemObject->GetStringField(TEXT("RowName")));
						EGEARTYPE GearType = (EGEARTYPE)ItemObject->GetNumberField(TEXT("GearType"));
						AddInitGear(RowName, GearType);
					}
				}

			}

			int  SlotItem = -1;
			JsonObject->TryGetNumberField("QuickItemSlot1", SlotItem);
			SetAttachQuickSlot(0, SlotItem);
			JsonObject->TryGetNumberField("QuickItemSlot2", SlotItem);
			SetAttachQuickSlot(1, SlotItem);
			JsonObject->TryGetNumberField("QuickItemSlot3", SlotItem);
			SetAttachQuickSlot(2, SlotItem);
			JsonObject->TryGetNumberField("QuickItemSlot4", SlotItem);
			SetAttachQuickSlot(3, SlotItem);


		}
		
	}
	

}

void UPlayerInventorySubsystem::SetAttachQuickSlot(int QuickSlotIndex, int ItemIndex)
{
	QuickItemSlotsPointer[QuickSlotIndex] = ItemIndex;
}

void UPlayerInventorySubsystem::AttachSlot(ERPGSLOTTYPE SlotType , URPGSlot* slot)
{
	switch (SlotType)
	{
	case ERPGSLOTTYPE::QUICK_ITEM:
	{
		QuickItemSlots.Add(slot);
		break;
	}
	default:
		break;
	}
}

int UPlayerInventorySubsystem::GetQuickSlotFromIndex(int QuickSlotIndex)
{
	return QuickItemSlotsPointer[QuickSlotIndex];
}

void UPlayerInventorySubsystem::QuickSlotClear(int8 QuickSlotIndex)
{
	QuickItemSlotsPointer[QuickSlotIndex] = -1;
}

int UPlayerInventorySubsystem::CheckQuickSlotItem(int ItemIndex)
{
	int select = -1;
	for (int8 i = 0; i < QuickItemSlotsPointer.Num(); i++)
	{
		if (QuickItemSlotsPointer[i] == ItemIndex)
		{
			select = i;
			return select;
		}
	}

	return -1;
}


