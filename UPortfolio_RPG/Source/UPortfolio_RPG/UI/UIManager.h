// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UI/UIEnum.h"
#include "UIManager.generated.h"


UCLASS()
class UPORTFOLIO_RPG_API AUIManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUIManager();

	static TWeakObjectPtr<AUIManager> UIManager;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;
public :
	TSubclassOf<UUserWidget> MainUIBP;
	class URPGMainUserWidget* PlayerUI;
	
public  :
	bool isShopOpen;


public:
	void PlayerGoodsUIRefresh();
	void ShowItemBox(FVector2D SpawnPos , struct  FItemData* Data);
	void HideItemBox();
};
