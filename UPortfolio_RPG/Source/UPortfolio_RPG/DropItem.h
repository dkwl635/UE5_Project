// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DropItem.generated.h"

class ADropItem;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemRemovedDelegate, ADropItem*, RemoveDropItem);

UCLASS()
class UPORTFOLIO_RPG_API ADropItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADropItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ItemHande;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int ItemCount;

public:
	UFUNCTION(BlueprintCallable)
	void SetDropItem(FName ItemRowName, int Count = 1);
	UFUNCTION(BlueprintImplementableEvent)
	void ActionDropItem();

	UFUNCTION(BlueprintCallable)
	FText SetItemText();

	UFUNCTION(BlueprintCallable)
	void AddItem();
	void RetrunItem();

	UPROPERTY()
	FItemRemovedDelegate OnRemoveItem;
};
