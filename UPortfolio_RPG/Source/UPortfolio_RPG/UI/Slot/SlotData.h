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
	virtual UTexture2D* GetSlotImg();
	 //����Ŭ�� ����
	virtual bool NormalUse();	
	//�ٸ� ���
	virtual bool QuickUse();
	//�ָ���� ��Ŭ�� + shift �� ����Ű�� �ٸ�������� ���
	//���� �����ϱ� ��..
	virtual bool SpecialUse();

};
