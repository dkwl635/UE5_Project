#pragma once
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "SlotEnum.h"
#include "SlotData.generated.h"


UCLASS()
class UPORTFOLIO_RPG_API USlotData : public UObject
{
	GENERATED_BODY()

public:
	USlotData();
public:
	static TWeakObjectPtr<UWorld> SlotWorld;
	static TWeakObjectPtr<class UPlayerInventorySubsystem> InventorySubsystem;
	static void ClearStaticMember();
public:
	ERPGSLOTTYPE SlotType;
	int32 SlotIndex;

public :
	//check data is valid
	virtual bool IsValid();
	//Setting data
	virtual void SetData();
	//Data refresh
	virtual void RefreshData();
	//Data Clear
	virtual void ClearData();
	//Get Image
	virtual UTexture2D* GetSlotImg();
	//Get Count
	virtual int32 GetCount();
	//double click Event
	virtual bool NormalUse();	
//virtual bool QuickUse();
//virtual bool SpecialUse();

	//ShowItem
	virtual  struct FItemData* GetItemData();


};
