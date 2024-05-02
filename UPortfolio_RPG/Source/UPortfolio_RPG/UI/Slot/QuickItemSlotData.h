#pragma once
#include "CoreMinimal.h"
#include "SlotData.h"

#include "QuickItemSlotData.generated.h"

USTRUCT(BlueprintType)
struct UPORTFOLIO_RPG_API FQuickItemSlotData : public FSlotData
{
	GENERATED_BODY()

public:
	FQuickItemSlotData();

	// USlotData을(를) 통해 상속됨
	bool IsValid() override;
	UTexture2D* GetSlotImg() override;
	bool NormalUse() override;
};
