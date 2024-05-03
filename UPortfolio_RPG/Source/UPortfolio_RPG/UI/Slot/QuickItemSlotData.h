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
	// USlotData을(를) 통해 상속됨
	bool IsValid() override;
	UTexture2D* GetSlotImg() override;
	bool NormalUse() override;

public:
	void SetSlotData(class UInventorySlotData* Data);

public :

	int InventoryItemIndex = -1;
	//임시로 가지고 있는 아이템 정보
	TWeakPtr<struct  FItemData> ItemData;
};
