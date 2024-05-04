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
	//�����Ͱ� ��ȿ üũ
	virtual bool IsValid();
	//������ �����ϱ�
	virtual void SetData();
	//������ ����
	virtual void RefreshData();
	//������ �ʱ�ȭ
	virtual void ClearData();
	//���� �̹��� 
	virtual UTexture2D* GetSlotImg();
	 //����Ŭ�� ����
	virtual bool NormalUse();	
	//�ٸ� ���
	virtual bool QuickUse();
	//�ָ���� ��Ŭ�� + shift �� ����Ű�� �ٸ�������� ���
	//���� �����ϱ� ��..
	virtual bool SpecialUse();

};