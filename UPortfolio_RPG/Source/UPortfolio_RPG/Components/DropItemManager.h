// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Queue.h"
#include "DropItemManager.generated.h"

UCLASS()
class UPORTFOLIO_RPG_API ADropItemManager : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ADropItemManager();
	~ADropItemManager();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ADropItem> DropItemClass;

	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	TArray<ADropItem*> DropItemList;
private:
	TQueue< ADropItem*> Pool;
	
public:
	UFUNCTION(BlueprintCallable)
	ADropItem* SpawnDropItem(FVector SpawnLocation);
	UFUNCTION()
	void PushBackItem(ADropItem* DropItem);

};

