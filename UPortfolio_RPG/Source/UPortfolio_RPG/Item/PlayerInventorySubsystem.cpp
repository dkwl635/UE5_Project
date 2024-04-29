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



	//가방에 들어가는 체크
	if (!IsAddable(Data, Count))
	{
		return false;
	}

	return	MoveItemToInventory(Data, Count);

}

bool UPlayerInventorySubsystem::IsAddable(FItemData* ItemData, int8 Count)
{
	//아이템 이름으로 키값지정
	FName ItemName = ItemData->ItemName;
	//남은 아이템 갯수
	int8 RemainingCount = Count;
	//인벤토리 크기
	int8 InvenSize = Inventory.Num();
	//가방에 같은 아이템이 있는 가방인덱스
	int8 CheckInvenIndex = FindItemInInventory(ItemName, 0);
	//가방 전체를 돌때까지
	while (CheckInvenIndex < InvenSize)
	{
		
		//만약 전부 순회 했다면
		if (CheckInvenIndex >= InvenSize)
			break;
		//남은 공간 계산
		int EmptySize = Inventory[CheckInvenIndex]->MaxBundleCount - Inventory[CheckInvenIndex]->CurrentBundleCount;
		//공간이 부족한지 체크
		RemainingCount -= EmptySize;
		//전부다 들어가면 성공
		if (RemainingCount <= 0)
		{
			return  true;
		}

		//같은 아이템이있는 위치 찾기
		CheckInvenIndex = FindItemInInventory(ItemName, CheckInvenIndex + 1);
	}
	
	//만약 전부 들어갔다면 (이건 없어도 될꺼 같기도)
	if (RemainingCount <= 0)
	{
		return  true;
	}
	
	//이제 아예 빈공간을 찾고 남은 재고 확인
	int8 EmptyIndex = FindEmptyInventory(0);
	//UE_LOG(LogTemp, Warning, TEXT("CheckInvenIndex: %d : %d : %d"), EmptyIndex , RemainingCount, ItemData->MaxBundleCount);
	//return  true;
	while (EmptyIndex < InvenSize)
	{

		//남은공간에 넣고 남은제고 확인
		RemainingCount -= ItemData->MaxBundleCount;
		if (RemainingCount <= 0)
		{
			return  true;
		}
		EmptyIndex = FindEmptyInventory(EmptyIndex);
	}

	//만약 전부 들어갔다면 (이건 없어도 될꺼 같기도)
	if (RemainingCount <= 0)
	{
		return  true;
	}

	return false;
}
//같은 아이템이 가방에 있는지 그리고 최대치가 남아있다면
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
	//아이템 이름으로 키값지정
	FName ItemName = ItemData->ItemName;
	//남은 아이템 갯수
	int8 RemainingCount = Count;
	//인벤토리 크기
	int8 InvenSize = Inventory.Num();
	//가방에 같은 아이템이 있는 가방인덱스
	int8 CheckInvenIndex = FindItemInInventory(ItemName);
	//가방 전체를 돌때까지
	while (CheckInvenIndex < InvenSize)
	{
		//만약 전부 순회 했다면
		if (CheckInvenIndex >= InvenSize)
			break;
		//남은 공간 계산
		int8 EmptySize = Inventory[CheckInvenIndex]->MaxBundleCount - Inventory[CheckInvenIndex]->CurrentBundleCount;
		//남은 공간이 있다면
		if (EmptySize > 0)
		{
			//얼마나 넣을꺼진
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
	
		//전부다 들어가면 성공
		if (RemainingCount <= 0)
		{
			return  true;
		}
	}

	//만약 전부 들어갔다면 (이건 없어도 될꺼 같기도)
	if (RemainingCount <= 0)
	{
		return  true;
	}

	//이제 아예 빈공간을 찾고 남은 재고 확인
	int8 EmptyIndex = FindEmptyInventory();
	while (EmptyIndex < InvenSize)
	{
		//얼마나 넣을꺼진
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

	//만약 전부 들어갔다면 (이건 없어도 될꺼 같기도)
	if (RemainingCount <= 0)
	{
		return  true;
	}

	//만약 여기서 실패하면 문제 있는거
	//이미 자리확인하고 왔으니
	ensure(false);
	return false;
}
