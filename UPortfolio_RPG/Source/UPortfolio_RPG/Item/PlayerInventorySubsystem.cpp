// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/PlayerInventorySubsystem.h"
#include "UObject/ConstructorHelpers.h"
#include "Item/Item.h"


bool UPlayerInventorySubsystem::Init()
{	
	Inventory.SetNum(MaxInvenSize, false);

	DataSubsystem = GetWorld()->GetGameInstance()->GetSubsystem<UDataSubsystem>();
	//UItem::DataSubsystem = DataSubsystem;

	if (!DataSubsystem)
	{
		return false;
	}


	ItemClass = UItem::StaticClass()->GetDefaultObject<UItem>();
	ItemClass->UseItem(nullptr , nullptr);

	AddItem( TEXT("HP100"), 10);
	ItemClass->UseItem(nullptr, Inventory[0].Get());
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



	//���濡 ���� üũ
	if (!IsAddable(Data, Count))
	{
		return false;
	}

	return	MoveItemToInventory(Data, Count);

}

bool UPlayerInventorySubsystem::IsAddable(FItemData* ItemData, int8 Count)
{
	//������ �̸����� Ű������
	FName ItemName = ItemData->ItemName;
	//���� ������ ����
	int8 RemainingCount = Count;
	//�κ��丮 ũ��
	int8 InvenSize = Inventory.Num();
	//���濡 ���� �������� �ִ� �����ε���
	int8 CheckInvenIndex = FindItemInInventory(ItemName, 0);
	//���� ��ü�� ��������
	while (CheckInvenIndex < InvenSize)
	{
		
		//���� ���� ��ȸ �ߴٸ�
		if (CheckInvenIndex >= InvenSize)
			break;
		//���� ���� ���
		int EmptySize = Inventory[CheckInvenIndex]->MaxBundleCount - Inventory[CheckInvenIndex]->CurrentBundleCount;
		//������ �������� üũ
		RemainingCount -= EmptySize;
		//���δ� ���� ����
		if (RemainingCount <= 0)
		{
			return  true;
		}

		//���� ���������ִ� ��ġ ã��
		CheckInvenIndex = FindItemInInventory(ItemName, CheckInvenIndex + 1);
	}
	
	//���� ���� ���ٸ� (�̰� ��� �ɲ� ���⵵)
	if (RemainingCount <= 0)
	{
		return  true;
	}
	
	//���� �ƿ� ������� ã�� ���� ��� Ȯ��
	int8 EmptyIndex = FindEmptyInventory(0);
	//UE_LOG(LogTemp, Warning, TEXT("CheckInvenIndex: %d : %d : %d"), EmptyIndex , RemainingCount, ItemData->MaxBundleCount);
	//return  true;
	while (EmptyIndex < InvenSize)
	{

		//���������� �ְ� �������� Ȯ��
		RemainingCount -= ItemData->MaxBundleCount;
		if (RemainingCount <= 0)
		{
			return  true;
		}
		EmptyIndex = FindEmptyInventory(EmptyIndex);
	}

	//���� ���� ���ٸ� (�̰� ��� �ɲ� ���⵵)
	if (RemainingCount <= 0)
	{
		return  true;
	}

	return false;
}
//���� �������� ���濡 �ִ��� �׸��� �ִ�ġ�� �����ִٸ�
int8 UPlayerInventorySubsystem::FindItemInInventory(const FName& ItemName, int8 StartIndex = 0)
{
	int8 Size = Inventory.Num();
	for (int8 i = StartIndex; i < Size; i++)
	{
		TSharedPtr<FItemData> ItemData = Inventory[i];
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

int8 UPlayerInventorySubsystem::FindEmptyInventory(int8 StartIndex = 0)
{
	int8 Size = Inventory.Num();
	for (int8 i = StartIndex; i < Size; i++)
	{
		if (Inventory[i] == nullptr)
		{
			return i;
		}
	}

	return Size;
}

bool UPlayerInventorySubsystem::MoveItemToInventory(FItemData* ItemData, int8 Count)
{
	//������ �̸����� Ű������
	FName ItemName = ItemData->ItemName;
	//���� ������ ����
	int8 RemainingCount = Count;
	//�κ��丮 ũ��
	int8 InvenSize = Inventory.Num();
	//���濡 ���� �������� �ִ� �����ε���
	int8 CheckInvenIndex = FindItemInInventory(ItemName);
	//���� ��ü�� ��������
	while (CheckInvenIndex < InvenSize)
	{
		//���� ���� ��ȸ �ߴٸ�
		if (CheckInvenIndex >= InvenSize)
			break;
		//���� ���� ���
		int8 EmptySize = Inventory[CheckInvenIndex]->MaxBundleCount - Inventory[CheckInvenIndex]->CurrentBundleCount;
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
			Inventory[CheckInvenIndex]->CurrentBundleCount += AddCount;
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
	int8 EmptyIndex = FindEmptyInventory();
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
		Inventory[EmptyIndex] = NewItemData;

		if (RemainingCount <= 0)
		{
			return  true;
		}
		EmptyIndex = FindEmptyInventory();
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
