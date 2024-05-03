#pragma once
#include "CoreMinimal.h"
#include "SlotData.h"
#include "QuickItemSlotData.generated.h"

UCLASS()
class UPORTFOLIO_RPG_API UQuickItemSlotData : public USlotData
{
	GENERATED_BODY()

public:

	TWeakObjectPtr<class URPGQuickSlotUserWidget> Helper;

public:
	UQuickItemSlotData();
	// USlotData��(��) ���� ��ӵ�
	bool IsValid() override;
	UTexture2D* GetSlotImg() override;
	bool NormalUse() override;

public:
	void SetSlotData(class UInventorySlotData* Data);

public :

	int InventoryItemIndex = -1;
	//�ӽ÷� ������ �ִ� ������ ����
	TWeakPtr<struct  FItemData> ItemData;
};
