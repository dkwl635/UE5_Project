// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PlayerInventorySubsystem.h"
#include "DataSubsystem/DataSubsystem.h"
#include "UI/RPGSlotUserWidget.h"
#include "Item.h"


bool UPlayerInventorySubsystem::Init()
{	
	NormalInventory.SetNum(MaxInvenSize, false);
	GearInventory.SetNum(MaxInvenSize, false);

	DataSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDataSubsystem>();
	//UItem::DataSubsystem = DataSubsystem;

	if (!DataSubsystem)
	{
		return false;
	}


	ItemClass = UItem::StaticClass()->GetDefaultObject<UItem>();

	AddItem( TEXT("HP100"), 3);
	AddItem( TEXT("HP200"), 3);
	//ItemClass->UseItem(nullptr, NormalInventory[0].Get());
	return true;

	
}

bool UPlayerInventorySubsystem::AddItem(const FName& InKey, int8 Count = 1)
{
	FItemData* Data = DataSubsystem->FindItem(InKey);
	if (!Data)
	{
		check(false);
		return false;
	}

	Inventory Inventory = GetInventory(Data->ItemType);

	//���濡 ���� üũ
	if (!IsAddable(Inventory ,Data, Count))
	{
		return false;
	}

	return	MoveItemToInventory(Inventory ,Data, Count);

}

bool UPlayerInventorySubsystem::IsAddable(Inventory Inventory,FItemData* ItemData, int8 Count)
{
	//������ �̸����� Ű������
	FName ItemName = ItemData->ItemName;
	//���� ������ ����
	int8 RemainingCount = Count;
	//�κ��丮 ũ��
	int8 InvenSize = Inventory->Num();
	//���濡 ���� �������� �ִ� �����ε���
	int8 CheckInvenIndex = FindItemInInventory(Inventory,ItemName, 0);
	//���� ��ü�� ��������
	while (CheckInvenIndex < InvenSize)
	{
		
		//���� ���� ��ȸ �ߴٸ�
		if (CheckInvenIndex >= InvenSize)
			break;
		//���� ���� ���
		int EmptySize = (*Inventory)[CheckInvenIndex]->MaxBundleCount - (*Inventory)[CheckInvenIndex]->CurrentBundleCount;
		//������ �������� üũ
		RemainingCount -= EmptySize;
		//���δ� ���� ����
		if (RemainingCount <= 0)
		{
			return  true;
		}

		//���� ���������ִ� ��ġ ã��
		CheckInvenIndex = FindItemInInventory(Inventory,ItemName, CheckInvenIndex + 1);
	}
	
	//���� ���� ���ٸ� (�̰� ��� �ɲ� ���⵵)
	if (RemainingCount <= 0)
	{
		return  true;
	}
	
	
	int8 EmptyIndex = FindEmptyInventory(Inventory,0);

	while (EmptyIndex < InvenSize)
	{

		//���������� �ְ� �������� Ȯ��
		RemainingCount -= ItemData->MaxBundleCount;
		if (RemainingCount <= 0)
		{
			return  true;
		}
		EmptyIndex = FindEmptyInventory(Inventory,EmptyIndex);
	}

	//���� ���� ���ٸ� (�̰� ��� �ɲ� ���⵵)
	if (RemainingCount <= 0)
	{
		return  true;
	}

	return false;
}
//���� �������� ���濡 �ִ��� �׸��� �ִ�ġ�� �����ִٸ�
int8 UPlayerInventorySubsystem::FindItemInInventory(Inventory Inventory, const FName& ItemName, int8 StartIndex = 0)
{
	int8 Size = Inventory->Num();
	for (int8 i = StartIndex; i < Size; i++)
	{
		TSharedPtr<FItemData> ItemData = (*Inventory)[i];
		if (ItemData == nullptr) { continue; }
		if (ItemData->ItemName == ItemName) 
		{
			if (ItemData->CurrentBundleCount < ItemData->MaxBundleCount)
			{
				return i;
			}
			continue;
		}
	}

	return Size;

}

int8 UPlayerInventorySubsystem::FindEmptyInventory(Inventory Inventory , int8 StartIndex = 0)
{
	int8 Size = Inventory->Num();
	for (int8 i = StartIndex; i < Size; i++)
	{
		if ( (*Inventory)[i]  == nullptr)
		{
			return i;
		}
	}

	return Size;
}

bool UPlayerInventorySubsystem::MoveItemToInventory(Inventory Inventory ,FItemData* ItemData, int8 Count)
{
	//������ �̸����� Ű������
	FName ItemName = ItemData->ItemName;
	//���� ������ ����
	int8 RemainingCount = Count;
	//�κ��丮 ũ��
	int8 InvenSize = Inventory->Num();
	//���濡 ���� �������� �ִ� �����ε���
	int8 CheckInvenIndex = FindItemInInventory(Inventory,ItemName);
	//���� ��ü�� ��������
	while (CheckInvenIndex < InvenSize)
	{
		//���� ���� ��ȸ �ߴٸ�
		if (CheckInvenIndex >= InvenSize)
			break;
		//���� ���� ���
		int8 EmptySize = (*Inventory)[CheckInvenIndex]->MaxBundleCount - (*Inventory)[CheckInvenIndex]->CurrentBundleCount;
		//���� ������ �ִٸ�
		if (EmptySize > 0)
		{
			//�󸶳� ��������
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
		else
		{
			continue;
		}
	
		//���δ� ���� ����
		if (RemainingCount <= 0)
		{
			return  true;
		}
	}

	//���� ���� ���ٸ� (�̰� ��� �ɲ� ���⵵)
	if (RemainingCount <= 0)
	{
		return  true;
	}

	//���� �ƿ� ������� ã�� ���� ��� Ȯ��
	int8 EmptyIndex = FindEmptyInventory(Inventory);
	while (EmptyIndex < InvenSize)
	{
		//�󸶳� ��������
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

		if (RemainingCount <= 0)
		{
			return  true;
		}
		EmptyIndex = FindEmptyInventory(Inventory);
	}

	//���� ���� ���ٸ� (�̰� ��� �ɲ� ���⵵)
	if (RemainingCount <= 0)
	{
		return  true;
	}

	//���� ���⼭ �����ϸ� ���� �ִ°�
	//�̹� �ڸ�Ȯ���ϰ� ������
	ensure(false);
	return false;
}

void UPlayerInventorySubsystem::ClearTempData()
{
}

void UPlayerInventorySubsystem::UseItem(Inventory Inventory, int8 InventoryIndex , int8 count = 1)
{
	if (!Inventory || count <= 0)
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("UseItem : %d : %d") , InventoryIndex , count);
	FItemData* data = (*Inventory)[InventoryIndex].Get();
	if(!data)
	{
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("UseItem__ : %s : %d"), *data->ItemName.ToString(), data->CurrentBundleCount);
	int NewCount = (data->CurrentBundleCount - count);
	if (NewCount <= 0)
	{
		(*Inventory)[InventoryIndex] = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("UseItem 00"));
	}
	else
	{
		data->CurrentBundleCount = NewCount;
	}

	ItemClass->UseItem(nullptr, data);
	GEngine->ForceGarbageCollection(true);
	
}

FItemData* UPlayerInventorySubsystem::GetItemInfo(Inventory Inventory, int8 InventoryIndex)
{
	if(InventoryIndex < 0 || !Inventory)
	{
		return nullptr;
	}

	return (*Inventory)[InventoryIndex].Get();
}

TArray<TSharedPtr<FItemData>>* UPlayerInventorySubsystem::GetInventory(EITEMTYPE ItemType)
{
	if (ItemType == EITEMTYPE::GEAR)
	{
		return &GearInventory;
	}
	else
	{
		return &NormalInventory;
	}

}

void UPlayerInventorySubsystem::QuickSlotRefresh(int8 QuickSlotIndex)
{

}

