#pragma once
#include "CoreMinimal.h"
#include "SlotData.h"
#include "QuickItemSlotData.generated.h"

UCLASS()
class UPORTFOLIO_RPG_API UQuickItemSlotData : public USlotData
{
	GENERATED_BODY()

public:
	UQuickItemSlotData();
	// USlotData을(를) 통해 상속됨
	bool IsValid() override;
	UTexture2D* GetSlotImg() override;
	bool NormalUse() override;
	void ClearData() override;
	void RefreshData() override;
	int32 GetCount() override;
	 struct FItemData* GetItemData() override;
	
public :
	//TWeakObjectPtr<class URPGSlotUserWidget> OrginSlot;
	int InventoryItemIndex = -1;
	int QuickSlotIndex = -1;
	TWeakPtr<FItemData> TempData;

};
