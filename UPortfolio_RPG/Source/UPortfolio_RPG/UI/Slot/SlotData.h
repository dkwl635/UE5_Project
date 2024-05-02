#pragma once
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "SlotData.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct UPORTFOLIO_RPG_API FSlotData 
{
	GENERATED_BODY()

public:
	static UWorld* World;

public:
	FSlotData();
	int32 SlotIndex;

public :
	//데이터가 유효 체크
	virtual bool IsValid();

	virtual UTexture2D* GetSlotImg();
	 //더블클릭 사용시
	virtual bool NormalUse();	
	//다른 방법
	virtual bool QuickUse();
	//애를들어 우클릭 + shift 등 조합키시 다른방법으로 사용
	//갯수 지정하기 등..
	virtual bool SpecialUse();

};
