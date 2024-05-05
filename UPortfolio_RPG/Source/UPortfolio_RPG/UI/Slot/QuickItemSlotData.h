#pragma once
#include "CoreMinimal.h"
#include "SlotData.h"
#include "QuickItemSlotData.generated.h"

UCLASS()
class UPORTFOLIO_RPG_API UQuickItemSlotData : public USlotData
{
	GENERATED_BODY()

public:

	TWeakObjectPtr<class URPGQuickSlotsUserWidget> Helper;

public:
	UQuickItemSlotData();
	// USlotData을(를) 통해 상속됨
	bool IsValid() override;
	UTexture2D* GetSlotImg() override;
	bool NormalUse() override;
	void ClearData() override;
	void RefreshData() override;
	int32 GetCount() override;

	
public :

	//원본 슬롯
	TWeakObjectPtr<class URPGSlotUserWidget> OrginSlot;

};
