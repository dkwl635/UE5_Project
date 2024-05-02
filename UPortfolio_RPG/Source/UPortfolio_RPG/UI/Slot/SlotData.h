#pragma once
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Item/PlayerInventorySubsystem.h"
#include "SlotData.generated.h"


UCLASS()
class UPORTFOLIO_RPG_API USlotData : public UObject
{
	GENERATED_BODY()

public:
	static  TWeakObjectPtr<UWorld> SlotWorld;
	static TWeakObjectPtr<UPlayerInventorySubsystem> InventorySubsystem;
	static void ClearStaticMember();
public:
	USlotData();
	int32 SlotIndex;

public :
	//�����Ͱ� ��ȿ üũ
	virtual bool IsValid();

	virtual UTexture2D* GetSlotImg();
	 //����Ŭ�� ����
	virtual bool NormalUse();	
	//�ٸ� ���
	virtual bool QuickUse();
	//�ָ���� ��Ŭ�� + shift �� ����Ű�� �ٸ�������� ���
	//���� �����ϱ� ��..
	virtual bool SpecialUse();

};
