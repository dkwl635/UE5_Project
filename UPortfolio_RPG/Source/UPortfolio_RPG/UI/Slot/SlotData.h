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
	static  TWeakObjectPtr<UWorld> SlotWorld;
	static TWeakObjectPtr<class UPlayerInventorySubsystem> InventorySubsystem;
	static void ClearStaticMember();
public:
	ERPGSLOTTYPE SlotType;
	int32 SlotIndex;

public :
	//데이터가 유효 체크
	virtual bool IsValid();
	//데이터 셋팅하기
	virtual void SetData();
	//데이터 갱신
	virtual void RefreshData();
	//데이터 초기화
	virtual void ClearData();
	//슬롯 이미지 
	virtual UTexture2D* GetSlotImg();
	 //더블클릭 사용시
	virtual bool NormalUse();	
	//다른 방법
	virtual bool QuickUse();
	//애를들어 우클릭 + shift 등 조합키시 다른방법으로 사용
	//갯수 지정하기 등..
	virtual bool SpecialUse();

};
